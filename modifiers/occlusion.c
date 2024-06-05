#include <stdio.h>

#include "occlusion.h"
#include "memory.h"
#include "hash.h"

audio_state_t state;

terrain_t concrete_wall = {90, 0.0f, 0.0f};
terrain_t wood_floor = {30, 0.0f, 0.0f};
terrain_t metal_grate = {20, 0.0f, 0.0f};
terrain_t wood_wall = {35, 0.0f, 0.0f};
terrain_t dirt_floor = {50, 0.0f, 0.0f};
terrain_t plastic_wall = {31, 0.0f, 0.0f};
terrain_t plastic_floor = {32, 0.0f, 0.0f};
terrain_t plastic_door = {33, 0.0f, 0.0f};

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
    state.materials->insert(state.materials, "Wood", &wood_wall);
    state.materials->insert(state.materials, "Plastic", &plastic_wall);
    state.materials->insert(state.materials, "Plastic", &plastic_floor);
    state.materials->insert(state.materials, "Plastic", &plastic_door);
    state.materials->insert(state.materials, "Dirt", &dirt_floor);
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
    // Print from map
    
    for (int i = 0; i < state.materials->size; i++) {
        printf("Material:  %s\n\t", state.materials->raw_data[i].string);
        for (int j = 0; j < state.materials->raw_data[i].n_items; j++) {
            printf("Density:   %5d\n\t", ((terrain_t *)state.materials->raw_data[i].data[j])->density);
            printf("Resonance: %5f\n\t", ((terrain_t *)state.materials->raw_data[i].data[j])->resonance);
            printf("Dampening: %5f\n\t", ((terrain_t *)state.materials->raw_data[i].data[j])->dampening);
        }
        printf("\n");
    }

    // Print manually from structures
    /*
    printf("Material:  %s\n\t", "Concrete Wall");
        printf("Density:   %5d\n\t", concrete_wall.density);
        printf("Resonance: %5f\n\t", concrete_wall.resonance);
        printf("Dampening: %5f\n", concrete_wall.dampening);
    printf("Material:  %s\n\t", "Wood Floor");
        printf("Density:   %5d\n\t", wood_floor.density);
        printf("Resonance: %5f\n\t", wood_floor.resonance);
        printf("Dampening: %5f\n", wood_floor.dampening);
    printf("Material:  %s\n\t", "Metal Grate");
        printf("Density:   %5d\n\t", metal_grate.density);
        printf("Resonance: %5f\n\t", metal_grate.resonance);
        printf("Dampening: %5f\n", metal_grate.dampening);
    printf("Material:  %s\n\t", "Wood Wall");
        printf("Density:   %5d\n\t", wood_wall.density);
        printf("Resonance: %5f\n\t", wood_wall.resonance);
        printf("Dampening: %5f\n", wood_wall.dampening);
    printf("Material:  %s\n\t", "Plastic Wall");
        printf("Density:   %5d\n\t", plastic_wall.density);
        printf("Resonance: %5f\n\t", plastic_wall.resonance);
        printf("Dampening: %5f\n", plastic_wall.dampening);
    printf("Material:  %s\n\t", "Plastic Floor");
        printf("Density:   %5d\n\t", plastic_floor.density);
        printf("Resonance: %5f\n\t", plastic_floor.resonance);
        printf("Dampening: %5f\n", plastic_floor.dampening);
    printf("Material:  %s\n\t", "Plastic Door");
        printf("Density:   %5d\n\t", plastic_door.density);
        printf("Resonance: %5f\n\t", plastic_door.resonance);
        printf("Dampening: %5f\n", plastic_door.dampening);
    printf("Material:  %s\n\t", "Dirt Floor");
        printf("Density:   %5d\n\t", dirt_floor.density);
        printf("Resonance: %5f\n\t", dirt_floor.resonance);
        printf("Dampening: %5f\n", dirt_floor.dampening);
    */
}