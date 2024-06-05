#include "types.h"
#include "inventory.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(void) {
    err ret = SUCCESS;
    uint8_t index = 0;
    Inv *construct;
    Inv *player;
    Inv *chest;
    Item tempi;
    Item tempii;
    Type tempw;
    Type tempf;

    MEM(construct, 1, Inv)
    construct->identity = "Construct";

    MEM(player, 1, Inv)
    player->identity = "Player";

    MEM(chest, 1, Inv)
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
    tempi.Type = tempw;
    tempi.Description = NULL;
    tempi.id = 1;

    tempii.Name = tempf.Name;
    tempii.Type = tempf;
    tempii.Description = NULL;
    tempii.id = 2;

    CHECK(get_Item(construct, tempii));
    CHECK(get_Item(construct, tempi));

    CHECK(sel_Item(&index, construct));
    CHECK(take_Item(construct, chest, index));
    CHECK(sel_Item(&index, construct));
    CHECK(take_Item(construct, player, index));
    CHECK(sel_Item(&index, player));
    CHECK(take_Item(player, chest, index));

    CHECK(view_inv(construct));
    CHECK(view_inv(chest));
    CHECK(view_inv(player));


exit:

    if (chest)
        free(chest);
    if (player)
        free(player);
    if (construct)
        free(construct);

    return ret;
}