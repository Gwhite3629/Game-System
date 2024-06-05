#ifndef _OCCLUSION_H_
#define _OCCLUSION_H_

#include "../utils/hash.h"

typedef struct terrain {
    int density;
    float resonance;
    float dampening;
} terrain_t;

typedef struct audio_state {
    map_t *materials;
} audio_state_t;

typedef err_t (*occlusion_callback_f) (void *, audio_state_t *);

typedef struct occlusion_modifier {
    void *mod_data;
    occlusion_callback_f mod_func;
} occlusion_modifier_t;

err_t occlusion_call(occlusion_modifier_t *mod);

void print_materials(void);

extern audio_state_t audio_state;

#endif // _OCCLUSION_H_