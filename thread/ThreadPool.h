#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include <set>
#include "Mutex.h"
#include "Condition.h"
#include "Task.h"
#include "Thread.h"

using std::set;

namespace thread {
    
class ThreadPool {
public:
    ThreadPool(int _num = 0);
    ~ThreadPool();
    
    Thread* get_idle_thread();
    
    void mv_idle_list(Thread* thr);
    void mv_busy_list(Thread* thr);

    int get_idle_nums();
    int get_busy_nums();
    
    void assign(Task* task);

private:
    int m_threads;

    set<Thread*> m_list_idle;
    Mutex m_mutex_idle;
    Condition m_cond_idle;
    
    set<Thread*> m_list_busy;
    Mutex m_mutex_busy;
    Condition m_cond_busy;

};

}

#endif