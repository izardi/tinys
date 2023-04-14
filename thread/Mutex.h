#ifndef _MUTEX_H_
#define _MUTEX_H_

#include <pthread.h>

namespace thread {

class Mutex{

friend class Condition;
friend class Alock;

public:
    Mutex(pthread_mutexattr_t* mattr = nullptr);
    ~Mutex();

    int lock();
    int try_lock();
    int unlock();

private:
    pthread_mutex_t m_mutex;
};

// 类似lock_guard
class Alock{

using mutextype = Mutex; 

public:
    explicit Alock(Mutex& _mtx);
    ~Alock() noexcept;
private:
    mutextype& mtx;
};

}

#endif
