#ifndef _AUDIO_H_
#define _AUDIO_H_

#include <pthread.h>

struct audio_state_t {
    pthread_cond_t *sync_cond;
    pthread_mutex_t *sync_lock;
    pthread_cond_t audio_cond;
    pthread_mutex_t audio_lock;
};

int init_audio(struct system_state_t *system_state);

extern struct audio_state_t *audio_state;

#endif // _AUDIO_H_