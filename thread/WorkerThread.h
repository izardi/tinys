#ifndef _WORKER_THREAD_H_
#define _WORKER_THREAD_H_

#include "Thread.h"

namespace thread {

class WorkerThread : public Thread {
public:
    WorkerThread();
    virtual ~WorkerThread();
    
    virtual void run();

    static void cleanup(void *ptr);
};

    
}

#endif