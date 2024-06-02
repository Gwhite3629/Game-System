#include <stdio.h>

#include "types.h"

err_t increment(void *v)
{
    unsigned int *base = (unsigned int *)v;

    (*base) = (*base) + 1;

    return 0;
}

err_t calc_score(void *alt, thread_state_t *t_state)
{
    int a_base = ((int *)alt)[0];
    int a_mult = ((int *)alt)[1];

    t_state->base_score += a_base;
    t_state->base_mult += a_mult;

    t_state->fin_score = t_state->base_score * t_state->base_mult;

    return 0;
}

unsigned int val = 2;

int main(void)
{
    simple_modifier_t inc;

    inc.mod_func = &increment;
    inc.mod_data = (void *)&val;

    printf("Before callback: %d\n", val);
    simple_call(&inc);
    printf("After callback:  %d\n", val);

    int thread_alterations[2] = {10, 2};

    complex_modifier_t alt;

    alt.mod_func = &calc_score;
    alt.mod_data = (void *)thread_alterations;

    printf("Before callback: %d = %d * %d\n", state.fin_score, state.base_score, state.base_mult);
    complex_call(&alt);
    printf("After callback:  %d = %d * %d\n", state.fin_score, state.base_score, state.base_mult);

    return 0;
}