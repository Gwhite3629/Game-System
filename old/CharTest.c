#include "types.h"
#include "utils.h"
#include "character.h"
#include "inventory.h"

#include <stdlib.h>
#include <stdio.h>

int main(void) {
    err_t ret = SUCCESS;
    Character *character = NULL;
    ret = init_char(&character);
    CHECK(ret);

    // printf("%p\n", character);
    view_inv(&(character->Inventory));
    int i = 0;
    while (character->Attacks[i].Name != NULL) {
        printf("Name: %s, Atk: %u, Type: %u\n", (*character).Attacks[i].Name, (*character).Attacks[i].Atk, (*character).Attacks[i].Type);
        i++;
    }

exit:
    clean_char(&character);
    return 0;
}