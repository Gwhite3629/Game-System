#include <pthread.h>

#include <engine/audio.h>
#include <utils/system.h>

struct audio_state_t *audio_state;

int init_audio(struct system_state_t *system_state)
{
    
}

void *audio_main(void *)
{
    double prev = getTime();
    double lag = 0.0f;

    while (1)
    {
        double cur = getTime();
        double elapsed = cur - prev;
        prev = cur;
        lag += elapsed;

        input();

        while (lag >= MS_PER_UPDATE)
        {
            update();
            lag -= MS_PER_UPDATE;
        }

        render();
    }
}