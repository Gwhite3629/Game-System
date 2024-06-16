#include <pthread.h>

#include <engine/audio.h>
#include <engine/physics.h>
#include <engine/graphics.h>
#include <engine/queue.h>

#include <utils/system.h>
#include <utils/memory.h>

struct system_state_t *system_state;

void input(void)
{

}

void update(void)
{

}

int main(void)
{
    int ret = SUCCESS;

    new(system_state, 1, struct system_state_t);

    CHECK(ret = pthread_cond_init(&system_state->sync_cond, NULL));
    CHECK(ret = pthread_mutex_init(&system_state->sync_lock, NULL));

    CHECK(ret = init_audio(system_state));
    CHECK(ret = init_physics(system_state));
    CHECK(ret = init_graphics(system_state));

    system_state->prev = getTime();
    double lag = 0.0f;

    while (1)
    {
        system_state->cur = getTime();
        double elapsed = system_state->cur - system_state->prev;
        system_state->prev = system_state->cur;
        lag += elapsed;

        input();

        do {
            update();
            lag -= MS_PER_UPDATE;
        } while (lag >= MS_PER_UPDATE);

        render();
    }

exit:

    return ret;
}