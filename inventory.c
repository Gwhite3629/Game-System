/*!
 * @file inventory.c
 *
 * @brief This function is responsible for all inventory operations.
 *
 * @author Grady White
 *
 * @date 2/2/2022
 *
 * Functions in this file are responsible for specific inventory
 * management operations and organization.
 *
 */

#include "types.h"
#include "utils.h"
#include "inventory.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

/*!
 * @brief Takes an item from one inventory to another
 *
 * Takes an item from source inventory and moves it to the first
 * open location in the destination inventory.
 *
 * @param[in] index Location of item to take
 *
 * @param[in,out] source Inventory containing target item
 * @param[in,out] destination Inventory to accept item
 *
 * @returns	The function returns SUCCESS if there are no errors, otherwise it returns
 *          errors according to the standard.
 *
 */
err take_Item(Inv *source, Inv *destination, uint8_t index)
{
  err ret = SUCCESS;
  int i = 0;

  CCHECK(destination->size, >, 32, WARNFULL)

  for (i = 0; i < 32; i++)
  {
    if (!destination->full[i])
    {
      source->slots[index].position = i;
      destination->slots[i] = source->slots[index];
      destination->size++;
      destination->full[i] = 1;
      CHECK(del_Item(source, index));
      source->slots[index].position = index;
      source->full[index] = 0;
      source->size--;
      break;
    }
  }

  printf("Item: %s moved from: %d in: %s to: %d in: %s\n",
         destination->slots[i].Name, index, source->identity,
         destination->slots[i].position, destination->identity);

exit:
  return ret;
}

/*!
 * @brief Places an item into destination inventory
 *
 * Places item into the first open location in destination inventory.
 *
 * @param[in] item Item to place in inventory
 *
 * @param[in,out] destination Inventory to accept item
 *
 * @returns	The function returns SUCCESS if there are no errors, otherwise it returns
 *          errors according to the standard.
 *
 */
err get_Item(Inv *destination, Item item)
{
  err ret = SUCCESS;
  int i = 0;

  CCHECK(destination->size, >, 32, WARNFULL);

  for (i = 0; i < 32; i++)
  {
    if (!destination->full[i])
    {
      destination->slots[i] = item;
      destination->slots[i].position = i;
      destination->size++;
      destination->full[i] = 1;
      break;
    }
  }
  printf("Item %s received into inventory %s at position %d\n",
         destination->slots[i].Name, destination->identity,
         destination->slots[i].position);

exit:
  return ret;
}

/*!
 * @brief Prints formatted inventory contents
 *
 * Prints all items in an inventory in order by index
 *
 * @param[in] source Inventory to view
 *
 * @returns	The function returns SUCCESS if there are no errors, otherwise it returns
 *          errors according to the standard.
 *
 */
err view_inv(Inv *source)
{
  err ret = SUCCESS;
  int i = 0;

  for (i = 0; i < 32; i++)
  {
    if (source->full[i])
    {
      printf("Item: %s of type: %s found at position: %u in inventory: %s\n",
             source->slots[i].Name, source->slots[i].Type.Name,
             source->slots[i].position, source->identity);
    }
  }

exit:
  return ret;
}

/*!
 * @brief Gets an item from a specifc index
 *
 * Function displays the inventory and asks the user to input
 * the desired index. Index is set and function returns.
 *
 * @param[in] source Inventory to get item from
 *
 * @param[out] index Index of item
 *
 * @returns	The function returns SUCCESS if there are no errors, otherwise it returns
 *          errors according to the standard.
 *
 */
err sel_Item(uint8_t *index, Inv *source)
{
  err ret = SUCCESS;
  bool exit = 0;
  CHECK(view_inv(source));

  while (!exit)
  {
    printf("Please enter a position: ");
    scanf("%hhd", index);
    if (!source->full[*index])
    {
      printf("Nothing found at position: %d, please try again\n", *index);
    }
    else
    {
      printf("Item: %s of type: %s found at position: %d in inventory: %s\n",
             source->slots[*index].Name, source->slots[*index].Type.Name,
             source->slots[*index].position, source->identity);
      exit = 1;
    }
  }

exit:
  return ret;
}

/*!
 * @brief Removes item from inventory
 *
 * This function created a Noting item and sets the index to that value
 *
 * @param[in] index Index of item to delete
 *
 * @param[in,out] source Inventory to delete item from
 *
 * @returns	The function returns SUCCESS if there are no errors, otherwise it returns
 *          errors according to the standard.
 *
 */
err del_Item(Inv *source, uint8_t index)
{
  err ret = SUCCESS;
  Item Nothing;
  Type null;
  null.Damage = 0;
  null.Health = 0;
  null.Hunger = 0;
  null.Poison = 0;
  null.Regen = 0;
  Nothing.Type = null;
  Nothing.id = 0;
  source->slots[index] = Nothing;
  source->full[index] = 0;

exit:
  return ret;
}

/*!
 * @brief Allocates character struct
 *
 * This function gives all pointers and arrays in the Character struct
 * their own heap memory.
 *
 * @param[in,out] character Double dereferenced pointer to Character
 *
 * @returns	The function returns SUCCESS if there are no errors, otherwise it returns
 *          errors according to the standard.
 *
 */
err alloc_char(Character **character)
{
  err ret = SUCCESS;
  int i;
  
  MEM((*character)->Inventory.identity, 64, char);

  for (i = 0; i < 32; i++)
  {
    MEM((*character)->Inventory.slots[i].Name, 64, char);

    MEM((*character)->Inventory.slots[i].Type.Name, 64, char);

    MEM((*character)->Inventory.slots[i].Description, 64, char);

    (*character)->Inventory.full[i] = false;
  }

  MEM((*character)->Personality, 64, char);

  MEM((*character)->Ideals, 64, char)

  MEM((*character)->Bonds, 64, char);

  MEM((*character)->Flaws, 64, char);

  MEM((*character)->Attacks, 20, Attack);

  for (i = 0; i < 20; i++)
  {
    MEM((*character)->Attacks[i].Name, 64, char);
  }
  
  return ret;

exit:
  clean_char(character);
  return ret;
}

/*!
 * @brief Destroys Character struct
 *
 * This function frees all memory allocated to a character.
 *
 * @param[in,out] character Character to be destroyed
 *
 * @returns	The function returns SUCCESS if there are no errors, otherwise it returns
 *          errors according to the standard.
 *
 */
err clean_char(Character **character)
{
  err ret = SUCCESS;
  uint i;

  if ((*character)->Inventory.identity)
    free((*character)->Inventory.identity);
  for (i = 0; i < 32; i++)
  {
    if ((*character)->Inventory.full[i])
    {
      if ((*character)->Inventory.slots[i].Name)
        free((*character)->Inventory.slots[i].Name);
      if ((*character)->Inventory.slots[i].Type.Name)
        free((*character)->Inventory.slots[i].Type.Name);
      if ((*character)->Inventory.slots[i].Description)
        free((*character)->Inventory.slots[i].Description);
    }
  }
  if ((*character)->Personality)
    free((*character)->Personality);
  if ((*character)->Ideals)
    free((*character)->Ideals);
  if ((*character)->Bonds)
    free((*character)->Bonds);
  if ((*character)->Flaws)
    free((*character)->Flaws);
  for (i = 0; i < sizeof((*character)->Attacks) / sizeof(Attack); i++)
  {
    if ((*character)->Attacks[i].Name)
      free((*character)->Attacks[i].Name);
  }
  if ((*character)->Attacks)
    free((*character)->Attacks);
  if ((*character))
    free((*character));

  return ret;
}
// err dump_Item() {}
// err drop_Item() {}