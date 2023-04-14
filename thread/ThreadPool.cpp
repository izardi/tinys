#include "ThreadPool.h"
#include "WorkerThread.h"
#include "../utility/Logger.hpp"

using namespace thread;
using namespace utility;

ThreadPool::ThreadPool(int _num): m_threads(_num) {
    for (int i = 0; i < _num; ++i) {
        Thread* thr = new WorkserThread();
        debug("create thread %x", thr);
    }
} 

ThreadPool::~ThreadPool(){}
