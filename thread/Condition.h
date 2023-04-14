#ifndef _CONDITION_H_
#define _CONDITION_H_

#include <pthread.h>
#include "Mutex.h"

namespace thread {

class Condition{
public:

    Condition(pthread_condattr_t * cond_attr = nullptr);
    ~Condition();

    int wait(Mutex* mutex);
    int signal();
    int broadcast();

protected:
    pthread_cond_t m_cond;
};

}

#endif
