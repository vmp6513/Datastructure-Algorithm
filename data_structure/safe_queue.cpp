#include <pthread.h>    //thread
#include <semaphore.h>  //thread sem
#include <stdio.h>
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
    Lock() { pthread_mutex_init(&_mutex, NULL); }
    ~Lock() { pthread_mutex_destroy(&_mutex); }
    void acquire() { pthread_mutex_lock(&_mutex); }
    void release() { pthread_mutex_unlock(&_mutex); }
    pthread_mutex_t *get() { return &_mutex; }

   private:
    pthread_mutex_t _mutex;
};

class Condition {
   public:
    Condition(pthread_mutex_t *lock) {
        pthread_cond_init(&_cond, NULL);
        _mutex = lock;
    }
    ~Condition() { pthread_cond_destroy(&_cond); }

    void wait() {
        pthread_mutex_lock(_mutex);
        pthread_cond_wait(&_cond, _mutex);
        pthread_mutex_unlock(_mutex);
    }

    void notify() { pthread_cond_signal(&_cond); }

    void acquire() { pthread_mutex_lock(_mutex); }

    void release() { pthread_mutex_unlock(_mutex); }

   private:
    pthread_cond_t _cond;
    pthread_mutex_t *_mutex;
};

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
    Queue(size_t max_size)
        : maxsize(max_size),
          unfinished_tasks(0),
          mutex(),
          not_empty(Condition(mutex.get())),
          not_full(Condition(mutex.get())),
          all_tasks_done(Condition(mutex.get())) {
        printf("[pid=%ld] create a deque, size=%ld\n", getpid(), maxsize);
    }
    ~Queue() {}
    void task_done();
    void join();
    size_t size();
    bool empty();
    bool full();

    void put(void *item, bool block = true, int timeout = 0) {
        not_full.acquire();

        if (maxsize > 0) {
            if (!block) {
            } else if (timeout == 0) {
                while (_qsize() >= maxsize) {
                    not_full.wait();
                }
            } else if (timeout < 0) {
                
            } else {
            }
        }
        queue.push_back(item);
        not_empty.notify();

        not_full.release();
    }
    void *get(bool block = true, int timeout = 0);
};

int main(int argc, char *argv[]) {
    Queue queue(20);

    return 0;
}
