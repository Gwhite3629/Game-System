#include "occlusion.h"
#include "types.h"

err_t fix_occlusion(void *fix, audio_state_t *audio)
{
    map_t *vals = (map_t *)fix;
    void *t = NULL;

    for (int i = 0; i < vals->size; i++) {
        t = audio->materials->lookup(audio->materials, vals->raw_data[i].string);
        if (t != NULL) {
            ((terrain_t *)t)->resonance = ((float *)vals->raw_data[i].data)[0];
            ((terrain_t *)t)->dampening = ((float *)vals->raw_data[i].data)[1];
        }
    }

    return 0;
}

int main(void)
{
    float concrete_vals[2] = {0.1f, 0.8f};
    float wood_vals[2] = {0.2f, 0.7f};
    float metal_vals[2] = {0.4f, 0.1f};

    map_t occlusion_vals;
    init_map(&occlusion_vals);
    occlusion_vals.insert(&occlusion_vals, "Concrete", &concrete_vals);
    occlusion_vals.insert(&occlusion_vals, "Wood", &wood_vals);
    occlusion_vals.insert(&occlusion_vals, "Metal", &metal_vals);

    occlusion_modifier_t mod;
    mod.mod_data = &occlusion_vals;
    mod.mod_func = &fix_occlusion;

    print_materials();
    occlusion_call(&mod);
    print_materials();
}