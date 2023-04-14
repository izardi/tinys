#ifndef _THREAD_H_
#define _THREAD_H_

#include "Mutex.h"
#include "Task.h"
#include "Condition.h"

namespace thread {

class Thread {
public:
    Thread();
    virtual ~Thread();
    
    virtual void run() = 0;
    
    void start();
    void stop();
    
    void set_task(Task* task);
    Task* get_task();
    
protected:
    static void* thread_func(void *ptr);
    
    pthread_t m_tid;
    Task* m_task;
    Mutex m_mutex;
    Condition m_cond;
};

    
}

#endif