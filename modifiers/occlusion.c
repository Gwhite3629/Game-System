#include <stdio.h>

#include "occlusion.h"
#include "hash.h"

audio_state_t state;

terrain_t concrete_wall = {90, 0.0f, 0.0f};
terrain_t wood_floor = {30, 0.0f, 0.0f};
terrain_t metal_grate = {20, 0.0f, 0.0f};

__attribute__ ((constructor)) static inline void init(void)
{
    int ret = SUCCESS;
	global_heap = create(ALIGN, 1*ALIGN, "global");
	VALID(global_heap, MEM_CODE, ALLOCATION_ERROR);

    map_t materials;
    CHECK(map_init(&materials));

    materials.insert(&materials, "Concrete", &concrete_wall);
    materials.insert(&materials, "Wood", &wood_floor);
    materials.insert(&materials, "Metal", &metal_grate);

    state.materials = &materials;
    
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