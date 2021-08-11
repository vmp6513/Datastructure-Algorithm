#include <errno.h>
#include <pthread.h>    //thread
#include <semaphore.h>  //thread sem
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>  //ipc msg queue
#include <sys/sem.h>  //ipc sem
#include <sys/shm.h>  //ipc shared mem
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <deque>
#include <exception>

class Lock {
   public:
    Lock() {
        pthread_mutexattr_init(&_mutexattr);
        // 跨进程共享
        pthread_mutexattr_setpshared(&_mutexattr, PTHREAD_PROCESS_SHARED);
        // 嵌套锁
        pthread_mutexattr_settype(&_mutexattr, PTHREAD_MUTEX_RECURSIVE);
        pthread_mutex_init(&_mutex, &_mutexattr);
    }
    ~Lock() {
        pthread_mutexattr_destroy(&_mutexattr);
        pthread_mutex_destroy(&_mutex);
    }
    void acquire() { pthread_mutex_lock(&_mutex); }
    void release() { pthread_mutex_unlock(&_mutex); }
    pthread_mutex_t *get() { return &_mutex; }

   private:
    pthread_mutex_t _mutex;
    pthread_mutexattr_t _mutexattr;
};

class Condition {
   public:
    Condition() {}
    Condition(Lock &mutex) {
        pthread_cond_init(&_cond, NULL);
        _mutex = mutex;
    }
    ~Condition() { pthread_cond_destroy(&_cond); }

    void wait() {
        pthread_mutex_lock(_mutex.get());
        pthread_cond_wait(&_cond, _mutex.get());
        pthread_mutex_unlock(_mutex.get());
    }

    void notify() { pthread_cond_signal(&_cond); }

    void acquire() { pthread_mutex_lock(_mutex.get()); }

    void release() { pthread_mutex_unlock(_mutex.get()); }

   private:
    pthread_cond_t _cond;
    Lock _mutex;
};

// 线程安全队列
class Queue {
   private:
    size_t maxsize;

    size_t unfinished_tasks;

    std::deque<void *> queue;

    Lock mutex;
    Condition not_empty;
    Condition not_full;
    Condition all_tasks_done;

    size_t _qsize() { return queue.size(); }

   public:
    Queue(size_t max_size) : maxsize(max_size), unfinished_tasks(0), mutex() {
        not_empty = Condition(mutex);
        not_full = Condition(mutex);
        all_tasks_done = Condition(mutex);
        printf("[pid=%ld] create a deque, size=%ld\n", pthread_self(), maxsize);
    }
    ~Queue() {}
    void task_done();
    void join();
    size_t size();
    bool empty();
    bool full();

    void put(void *item, bool block = true, int timeout = 0) {
        not_full.acquire();

        // TODO: 非阻塞
        if (!block) {
            if (_qsize() >= maxsize) {
                errno = EAGAIN;
                return;
            }
        }
        // 阻塞
        else {
            // 无超时
            if (timeout == 0) {
                while (_qsize() >= maxsize) {
                    not_full.wait();
                }
            }
            // TODO: 有超时
            else if (timeout > 0) {
            } else {
                throw std::exception();
            }
        }

        queue.push_back(item);
        not_empty.notify();
        unfinished_tasks += 1;

        not_full.release();
    }
    void *get(bool block = true, int timeout = 0) {
        not_empty.acquire();

        // TODO: 非阻塞
        if (!block) {
            if (_qsize() <= 0) {
                errno = EAGAIN;
                return NULL;
            }
        }
        // 阻塞
        else {
            // 无超时
            if (timeout == 0) {
                while (_qsize() == 0) {
                    not_empty.wait();
                }
            }
            // TODO: 有超时
            else if (timeout > 0) {
            } else {
                throw std::exception();
            }
        }

        void *item = queue.front();
        queue.pop_front();
        not_full.notify();

        not_empty.release();
        return item;
    }
};

void *consume(void *arg) {
    Queue *queue = (Queue *)arg;
    printf("[consumer:%ld] ready to consume...\n", pthread_self());

    while (true) {
        int *item;
        item = (int *)(queue->get(true));
        printf("[consumer:%ld] get a item %d\n", pthread_self(), *item);
    }
}

void *produce(void *arg) {
    Queue *queue = (Queue *)arg;
    printf("[producer:%ld] ready to produce...\n", pthread_self());

    while (true) {
        int *item = (int *)malloc(sizeof(int));
        *item = rand() % 100;
        queue->put(item, true);
        printf("[producer:%ld] put a item %d\n", pthread_self(), *item);
    }
}

int main(int argc, char *argv[]) {
    Queue queue(3);

    pthread_t consumer;
    pthread_t producer;

    pthread_create(&consumer, NULL, consume, &queue);
    pthread_create(&producer, NULL, produce, &queue);

    pthread_join(consumer, NULL);
    pthread_join(producer, NULL);

    return 0;
}
