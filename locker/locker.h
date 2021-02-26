#ifndef LOCKER_H
#define LOCKER_H

#include <exception>
#include <pthread.h>
#include <semaphore.h>

class CSemaphore {
public:
    CSemaphore();
    CSemaphore(int num);
    ~CSemaphore();
    bool wait();
    bool post();
private:
    sem_t m_sem;
};

class CMutex {
public:
    CMutex();
    ~CMutex();
    bool lock();
    bool unlock();
    pthread_mutex_t* getMutex();
private:
    pthread_mutex_t m_mutex;
};

class CCond {
public:
    CCond();
    ~CCond();
    bool wait(pthread_mutex_t* m_mutex);
    bool timewait(pthread_mutex_t* m_mutex, const struct timespec &t);
    bool signal();
    bool broadcast();
private:
    pthread_cond_t m_cond;
};

#endif