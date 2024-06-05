#include "occlusion.h"
#include "types.h"

err_t fix_occlusion(void *fix, audio_state_t *audio)
{
    map_t *vals = (map_t *)fix;
    void *t = NULL;

    /*
    for (int i = 0; i < vals->size; i++) {
        t = audio->materials->lookup(audio->materials, vals->raw_data[i].string);
        //printf("Target String: %s\n", vals->raw_data[i].string);
        if (t != NULL) {
            //printf("Found\n");
            ((terrain_t *)t)->resonance = ((float *)vals->raw_data[i].data)[0];
            ((terrain_t *)t)->dampening = ((float *)vals->raw_data[i].data)[1];
        }
        t = NULL;
    }
    */

    int iter = -1;
    int iter_inner = -1;
    void ****pairs = map_union(vals, audio->materials);
    while (pairs[++iter][0] != NULL) {
        while(pairs[iter][1][++iter_inner] != NULL) {
            ((terrain_t *)pairs[iter][1][iter_inner])->resonance = ((float *)pairs[iter][0][0])[0];
            ((terrain_t *)pairs[iter][1][iter_inner])->dampening = ((float *)pairs[iter][0][0])[1];
        }
        del(pairs[iter]);
        iter_inner = -1;
    }
    del(pairs);

exit:
    return 0;
}

int main(void)
{
    float concrete_vals[2] = {0.1f, 0.8f};
    float wood_vals[2] = {0.2f, 0.7f};
    float metal_vals[2] = {0.4f, 0.1f};
    float plastic_vals[2] = {0.5f, 0.4f};
    float air_vals[2] = {0.05f, 0.001f};

    map_t *occlusion_vals;
    new(occlusion_vals, 1, map_t);
    map_init(occlusion_vals);
    //printf("------ CREATING USER MAP ------\n");
    occlusion_vals->insert(occlusion_vals, "Concrete", &concrete_vals);
    occlusion_vals->insert(occlusion_vals, "Metal", &metal_vals);
    occlusion_vals->insert(occlusion_vals, "Wood", &wood_vals);
    occlusion_vals->insert(occlusion_vals, "Plastic", &plastic_vals);
    occlusion_vals->insert(occlusion_vals, "Air", &air_vals);
    //printf("-------  DONE USER MAP  -------\n");

    occlusion_modifier_t mod = {
        occlusion_vals,
        &fix_occlusion,
    };

    print_materials();
    printf("\n");
    occlusion_call(&mod);
    printf("\n");
    print_materials();
exit:
    return ret;
}