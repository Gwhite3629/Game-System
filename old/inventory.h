#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include "types.h"

err_t take_Item(Inv *source, Inv *destination, uint8_t index);
err_t get_Item(Inv *destination, Item item);
err_t view_inv(Inv *source);
err_t sel_Item(uint8_t *index, Inv *source);
err_t del_Item(Inv *source, uint8_t index);
err_t alloc_char(Character **character);
err_t init_Inv(Inv *source);
err_t clean_char(Character **character);

#endif // _INVENTORY_H_