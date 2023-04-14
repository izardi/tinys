#include "Mutex.h"

using namespace thread;

Mutex::Mutex( pthread_mutexattr_t* mattr) {
    pthread_mutexattr_init(mattr);
    pthread_mutexattr_settype(mattr, PTHREAD_MUTEX_ERRORCHECK);
    pthread_mutex_init(&m_mutex, mattr);
}
    
Mutex::~Mutex() {
    pthread_mutex_destroy(&m_mutex);
}

int Mutex::lock() {
    return pthread_mutex_lock(&m_mutex);
}

int Mutex::try_lock() {
    return pthread_mutex_trylock(&m_mutex);
}

int Mutex::unlock() {
    return pthread_mutex_unlock(&m_mutex);
}

Alock::Alock(mutextype& _mtx): mtx(_mtx){
    mtx.lock();
}

Alock::~Alock() noexcept{
    mtx.unlock();
}
