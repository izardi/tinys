#include "Thread.h"
#include <pthread.h>

using namespace thread;

Thread::Thread(): m_tid(0), m_task(nullptr){}

Thread::~Thread(){}

void Thread::start() {
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&m_tid, &attr, thread_func, (void*)this);
    pthread_attr_destroy(&attr);
}

void Thread::stop() {
    pthread_exit(PTHREAD_CANCELED);
}

void* Thread::thread_func(void *ptr) {
    Thread* thr = (Thread*)ptr;
    thr->run();
    return ptr;
}

void Thread::set_task(Task* task) {
    {
        Alock al(m_mutex);
        m_task = task;
    }
    m_cond.signal();
}

Task* Thread::get_task() {
    Alock al(m_mutex);
    return m_task;
}
