#include "types.h"
#include "character.h"
#include "inventory.h"

#include <stdlib.h>
#include <stdio.h>

int main(void) {
    uint ret = SUCCESS;
    Character *character;
    ret = init_char(&character);
    if (ret) {
        printf("Failed to create character: %u\n", ret);
        return -1;
    }
    // printf("%p\n", character);
    view_inv(&(character->Inventory));
    for (int i = 0; i<sizeof(*character->Attacks); i++) {
        printf("Name: %s, Atk: %u, Type: %u\n", (*character).Attacks[i].Name, (*character).Attacks[i].Atk, (*character).Attacks[i].Type);
    }

    clean_char(&character);
    return 0;
}