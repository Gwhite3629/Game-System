#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include "types.h"

err take_Item(Inv *source, Inv *destination, uint8_t index);
err get_Item(Inv *destination, Item item);
err view_inv(Inv *source);
err sel_Item(uint8_t *index, Inv *source);
err del_Item(Inv *source, uint8_t index);
err alloc_char(Character **character);
err init_Inv(Inv *source);
err clean_char(Character **character);

#endif // _INVENTORY_H_