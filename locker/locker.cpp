#include "locker.h"

CSemaphore::CSemaphore() {
    if(sem_init(&m_sem, 0, 0) != 0) {
        throw std::exception();
    }
}

CSemaphore::CSemaphore(int num) {
    if(sem_init(&m_sem, 0, num) != 0) {
        throw std::exception();
    }
}

CSemaphore::~CSemaphore() {
    sem_destroy(&m_sem);
}

bool CSemaphore::wait() {
    return sem_wait(&m_sem) == 0;
}

bool CSemaphore::post() {
    return sem_post(&m_sem) == 0;
}



CMutex::CMutex() {
    if(pthread_mutex_init(&m_mutex, nullptr) != 0) {
        throw std::exception();
    }
}

CMutex::~CMutex() {
    pthread_mutex_destroy(&m_mutex);
}

bool CMutex::lock() {
    return pthread_mutex_lock(&m_mutex) == 0;
}

bool CMutex::unlock() {
    return pthread_mutex_unlock(&m_mutex) == 0;
}

pthread_mutex_t* CMutex::getMutex() {
    return &m_mutex;
}


CCond::CCond() {
    if(pthread_cond_init(&m_cond, nullptr) != 0) {
        throw std::exception();
    }
}

CCond::~CCond() {
    pthread_cond_destroy(&m_cond);
}

bool CCond::wait(pthread_mutex_t* m_mutex) {
    return pthread_cond_wait(&m_cond, m_mutex) == 0;
}

bool CCond::timewait(pthread_mutex_t* mutex, const struct timespec &t) {
    return pthread_cond_timedwait(&m_cond, mutex, &t) == 0;
}

bool CCond::signal() {
    return pthread_cond_signal(&m_cond) == 0;
}

bool CCond::broadcast() {
    return pthread_cond_broadcast(&m_cond) == 0;
}