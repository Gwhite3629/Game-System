#ifndef _MOD_TYPES_H_
#define _MOD_TYPES_H_

#include "utils.h"

// This structure is presented as an example of a threads internal state that
// The complex_call function would have access to and pass to the complex
// Modifier function
typedef struct thread_state {
    int base_score;
    int base_mult;
    int fin_score;
} thread_state_t;

typedef err_t (*simple_callback_f) (void *);

typedef err_t (*complex_callback_f) (void *, thread_state_t *);

// This function is called by the simple_call function.
typedef struct simple_modifier {
    simple_callback_f mod_func;
    void *mod_data;
} simple_modifier_t;

// This object exists uniquely for each system within a thread.
// For example there would be a modifier for the occlusion system
// Which has access to the game terrain and the audio thread.
// There would therefore be some specific function template which
// The programmer could use to modify the specific occlusion thread state.
typedef struct complex_modifier {
    complex_callback_f mod_func;
    void *mod_data;
} complex_modifier_t;

// Used to execute functions that only modify internal or global values
// This function would be called on a queue of simple mod functions.
err_t simple_call(simple_modifier_t *mod);

// Used to execute complex functions according to a threads specific purpose
// This function is a placeholder for a threads internal loop and the complex
// Function would alter variables of the threads internal state according to
// The programmers function and input data
err_t complex_call(complex_modifier_t *mod);

extern thread_state_t state;

#endif // _MOD_TYPES_H_