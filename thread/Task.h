#ifndef _TASK_H_
#define _TASK_H_

#include "Mutex.h"

namespace thread{

class Task {
public:
    Task();
    Task(void *data);
    virtual ~Task();
    
    void* get_data();
    void set_data(void* data);
    
    virtual void run() = 0;
    virtual void destroy() = 0;
protected:
    void* m_data;
    Mutex m_mutex;
};

}

#endif