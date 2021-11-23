#include "types.h"
#include "inventory.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    uint8_t index = 0;
    Inv *construct;
    Inv *player;
    Inv *chest;
    Item tempi;
    Item tempii;
    Type tempw;
    Type tempf;

    construct = malloc(sizeof(Inv));
    if (construct == NULL) {
        perror("memory error");
        goto fail;
    }
    construct->identity = "Construct";

    player = malloc(sizeof(Inv));
    if (player == NULL) {
        perror("memory error");
        goto fail;
    }
    player->identity = "Player";

    chest = malloc(sizeof(Inv));
    if (chest == NULL) {
        perror("memory error");
        goto fail;
    }
    chest->identity = "Chest";

    tempw.Name = "Longsword";
    tempw.Damage = 10;
    tempw.Health = 120;
    tempw.Hunger = 0;
    tempw.Poison = 0;
    tempw.Regen = 0;

    tempf.Name = "Bread";
    tempf.Damage = 0;
    tempf.Hunger = 10;
    tempf.Health = 0;
    tempf.Poison = 0;
    tempf.Regen = 1;

    tempi.Name = tempw.Name;
    tempi.type_name = "Weapon";
    tempi.Type = tempw;
    tempi.Description = NULL;
    tempi.id = 1;

    tempii.Name = tempf.Name;
    tempii.type_name = "Food";
    tempii.Type = tempf;
    tempii.Description = NULL;
    tempii.id = 2;

    get_Item(construct, tempii);
    get_Item(construct, tempi);

    sel_Item(&index, construct);
    take_Item(construct, chest, index);
    sel_Item(&index, construct);
    take_Item(construct, player, index);
    sel_Item(&index, player);
    take_Item(player, chest, index);

    view_inv(construct);
    view_inv(chest);
    view_inv(player);

    free(chest);
    free(player);
    free(construct);
    return 0;
fail:

    free(chest);
    free(player);
    free(construct);
    return 1;
}