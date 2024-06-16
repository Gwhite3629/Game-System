#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include <pthread.h>

struct physics_state_t {
    pthread_cond_t *sync_cond;
    pthread_mutex_t *sync_lock;
    pthread_cond_t physics_cond;
    pthread_mutex_t physics_lock;
};

int init_physics(struct system_state_t *system_state);

extern struct physics_state_t *physics_state;

#endif // _PHYSICS_H_