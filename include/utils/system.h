#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#define MS_PER_UPDATE 4

/*
 * Returns the current time in ms.
 * 
 */
double getTime();

struct system_state_t {
    pthread_cond_t sync_cond;
    pthread_mutex_t sync_lock;
    double prev, cur;
};



#endif // _SYSTEM_H_