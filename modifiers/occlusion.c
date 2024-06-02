#include <stdio.h>

#include "occlusion.h"
#include "memory.h"
#include "hash.h"

audio_state_t state;

terrain_t concrete_wall = {90, 0.0f, 0.0f};
terrain_t wood_floor = {30, 0.0f, 0.0f};
terrain_t metal_grate = {20, 0.0f, 0.0f};

__attribute__ ((constructor)) static inline void init(void)
{
	global_heap = create(ALIGN, 1*ALIGN, "global");
	VALID(global_heap, MEM_CODE, ALLOCATION_ERROR);

    new(state.materials, 1, map_t);
    CHECK(map_init(state.materials));
    //printf("----- CREATING THREAD MAP -----\n");
    state.materials->insert(state.materials, "Concrete", &concrete_wall);
    state.materials->insert(state.materials, "Metal", &metal_grate);
    state.materials->insert(state.materials, "Wood", &wood_floor);
    //printf("------- DONE THREAD MAP -------\n");
    return;
exit:
	abort();
}

__attribute__ ((destructor)) static inline void end(void)
{
	destroy(global_heap);
}

err_t occlusion_call(occlusion_modifier_t *mod)
{
    return mod->mod_func(mod->mod_data, &state);
}

void print_materials(void)
{
    for (int i = 0; i < state.materials->size; i++) {
        printf("Material:  %s\n\t", state.materials->raw_data[i].string);
        printf("Density:   %5d\n\t", ((terrain_t *)state.materials->raw_data[i].data)->density);
        printf("Resonance: %5f\n\t", ((terrain_t *)state.materials->raw_data[i].data)->resonance);
        printf("Dampening: %5f\n", ((terrain_t *)state.materials->raw_data[i].data)->dampening);
    }
}