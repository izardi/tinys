#include "WorkerThread.h"
#include "../utility/Logger.hpp"
#include "../utility/Singleton.hpp"
#include <csignal>
#include <pthread.h>
#include <signal.h>
#include "ThreadPool.h"

using namespace utility;
using namespace thread;

WorkerThread::WorkerThread(): Thread(){};

WorkerThread::~WorkerThread() {}

void WorkerThread::cleanup(void *ptr) {
    info("worker thread cleanup handler: %x", ptr);
}

void WorkerThread::run() {
    sigset_t mask;
    if (0 != sigfillset(&mask)) {
        perror("sigfillset error");
    }

    if (0 != pthread_sigmask(SIG_SETMASK, &mask, nullptr)) {
        perror("pthread_sigmask() error");
    }
    
    pthread_cleanup_push(cleanup, this);

    while(true) {
        {
            Alock al(m_mutex);
            while (m_task == nullptr)
                m_cond.wait(&m_mutex);
        }
        
        int old_state = 0;
        int rc = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_state);
        m_task->run();
        m_task->destroy();
        m_task = nullptr;
        Singleton<ThreadPool>::instance()->mv_idle_list(this);
        rc = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &old_state);
        pthread_testcancel(); // 添加一个取消点，如果不可以cancel或者没有cancel则无效
    }

    pthread_cleanup_pop(1);
}


