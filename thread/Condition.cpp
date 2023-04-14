#include "Condition.h"

using namespace thread;

Condition::Condition(pthread_condattr_t * cond_attr) {
    pthread_cond_init(&m_cond, cond_attr);
}

Condition::~Condition() {
    pthread_cond_destroy(&m_cond);
}

int Condition::wait(Mutex* mutex) {
    return pthread_cond_wait(&m_cond, &(mutex->m_mutex));
}

int Condition::signal() {
    return pthread_cond_signal(&m_cond);
}

int Condition::broadcast() {
    return pthread_cond_broadcast(&m_cond);
}