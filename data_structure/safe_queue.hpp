#include <pthread.h>

#include <deque>
#include <exception>
#include <stdexcept>
#include <string>

class QueueFull : public std::exception {
   public:
    QueueFull(const std::string &msg = "The queue is full\n") : _msg(msg) {}
    const char *what() const noexcept { return _msg.c_str(); }

   private:
    std::string _msg;
};

class QueueEmpty : public std::exception {
   public:
    QueueEmpty(const std::string &msg = "The queue is empty\n") : _msg(msg) {}
    const char *what() const noexcept { return _msg.c_str(); }

   private:
    std::string _msg;
};

class Lock {
   public:
    Lock() {
        pthread_mutexattr_init(&_mutexattr);
        // 跨进程共享
        pthread_mutexattr_setpshared(&_mutexattr, PTHREAD_PROCESS_SHARED);
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
    Lock(const Lock &lock) {}
    Lock operator=(const Lock &lock) {}
    pthread_mutex_t _mutex;
    pthread_mutexattr_t _mutexattr;
};

class Condition {
   public:
    Condition() {}

    Condition(Lock &mutex) {
        pthread_cond_init(&_cond, NULL);
        _mutex = mutex.get();
    }
    ~Condition() { pthread_cond_destroy(&_cond); }

    void wait() {
        // =0 表示之前没有获取互斥锁, 记得后续要释放一次
        if (0 == pthread_mutex_trylock(_mutex)) {
            pthread_mutex_unlock(_mutex);
            throw std::runtime_error("Cannot wait on un-acquired lock");
        }
        pthread_cond_wait(&_cond, _mutex);
    }

    void notify() { pthread_cond_signal(&_cond); }

    void acquire() { pthread_mutex_lock(_mutex); }

    void release() { pthread_mutex_unlock(_mutex); }

   private:
    pthread_cond_t _cond;
    pthread_mutex_t *_mutex;
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
    size_t size() {
        mutex.acquire();
        size_t cur_size = _qsize();
        mutex.release();
        return cur_size;
    }
    bool empty();
    bool full();

    void put(void *item, bool block = true, int timeout = 0) {
        not_full.acquire();

        // 非阻塞
        if (!block) {
            if (_qsize() >= maxsize) {
                not_full.release();
                throw QueueFull();
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
                throw std::runtime_error("The timeout must a positive\n");
            }
        }

        queue.push_back(item);
        not_empty.notify();
        unfinished_tasks += 1;

        not_full.release();
    }
    void *get(bool block = true, int timeout = 0) {
        not_empty.acquire();
        // 非阻塞
        if (!block) {
            if (_qsize() <= 0) {
                not_empty.release();
                throw QueueEmpty();
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
                throw std::runtime_error("The timeout must a positive\n");
            }
        }

        void *item = queue.front();
        queue.pop_front();
        not_full.notify();

        not_empty.release();
        return item;
    }
};
