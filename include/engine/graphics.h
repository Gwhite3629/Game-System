#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <pthread.h>

struct graphics_state_t {
    pthread_cond_t *sync_cond;
    pthread_mutex_t *sync_lock;
    pthread_cond_t graphics_cond;
    pthread_mutex_t graphics_lock;
};

int init_graphics(struct system_state_t *system_state);

struct graphics_state_t *graphics_state;

#endif // _GRAPHICS_H_