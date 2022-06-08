/*!
 * @file Character.c
 * 
 * @brief This file keeps track of all character related functions
 * 
 * @author Grady White
 * 
 * @date 2/2/2022
 * 
 * Functions in this file are responsible for initializing character
 * data from a file, writing character data to a file, and creating
 * a new character.
 * 
 */

#include "types.h"
#include "utils.h"
#include "file.h"
#include "inventory.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

/*!
 * @brief Initialize a character from a file
 * 
 * Primary function for loading character data from a save file.
 * Characters inventory and stats are loaded into the Character struct.  
 * 
 * @param[in,out] character Pointer to a Character type pointer which contains all
 *                          relevant character data
 * 
 * @returns	The function returns SUCCESS if there are no errors, otherwise it returns
 *          errors according to the standard.
 * 
 */
err init_char(Character **character)
{
    err ret = SUCCESS;
    char *locator = NULL;
    bool done = 0;
    uint i;
    uint index;
    uint temp;
    char *dat;
    uint ret = SUCCESS;
    FILE *fd;
    fpos_t *char_start = NULL;
    fpos_t *char_end = NULL;
    fpos_t *cur_pos = NULL;
    
    MEM(dat, 64, char);
    
    MEM(char_start, 1, fpos_t);

    MEM(char_end, 1, fpos_t);

    MEM(cur_pos, 1, fpos_t);

    MEM(locator, 64, char);

    MEM((*character), 1, Character);

    // Get character positions
    printf("Select identifier:");
    scanf("%s", locator);

    VALID(fd = fopen("profile.cht", "r"), FILE_CODE, FILE_OPEN);

    CHECK(find_event(fd, char_start, char_end, locator));

    fsetpos(fd, char_start);
    // End character position

    CHECK(ret = alloc_char(character));

    // Inventory
    fscanf(fd, "%s\n", (*character)->Inventory.identity);
    fscanf(fd, "%u\n", &((*character)->Inventory.state));
    fscanf(fd, "%u\n", &((*character)->Inventory.size));
    for (i = 0; i < (*character)->Inventory.size; i++)
    {
        fscanf(fd, "%u\n", &index);
        (*character)->Inventory.slots[index].position = index;
        (*character)->Inventory.full[index] = true;
        fscanf(fd, "%s\n", (*character)->Inventory.slots[index].Name);
        fscanf(fd, "%s\n", (*character)->Inventory.slots[index].Type.Name);
        fscanf(fd, "%u\n", &((*character)->Inventory.slots[index].Type.Health));
        fscanf(fd, "%u\n", &((*character)->Inventory.slots[index].Type.Damage));
        fscanf(fd, "%u\n", &((*character)->Inventory.slots[index].Type.Hunger));
        fscanf(fd, "%u\n", &((*character)->Inventory.slots[index].Type.Poison));
        fscanf(fd, "%u\n", &((*character)->Inventory.slots[index].Type.Regen));
        fscanf(fd, "%s\n", (*character)->Inventory.slots[index].Description);
        fscanf(fd, "%u\n", &((*character)->Inventory.slots[index].id));
    }

    // Stats
    fscanf(fd, "%u\n", &((*character)->stat.Save.Strength));
    fscanf(fd, "%u\n", &((*character)->stat.Save.Dexterity));
    fscanf(fd, "%u\n", &((*character)->stat.Save.Constitution));
    fscanf(fd, "%u\n", &((*character)->stat.Save.Intelligence));
    fscanf(fd, "%u\n", &((*character)->stat.Save.Wisdom));
    fscanf(fd, "%u\n", &((*character)->stat.Save.Charisma));

    fscanf(fd, "%u\n", &temp);
    (*character)->stat.Skills.Acrobatics = temp;
    fscanf(fd, "%u\n", &temp);
    (*character)->stat.Skills.AnimalHandling = temp;
    fscanf(fd, "%u\n", &temp);
    (*character)->stat.Skills.Arcana = temp;
    fscanf(fd, "%u\n", &temp);
    (*character)->stat.Skills.Athletics = temp;
    fscanf(fd, "%u\n", &temp);
    (*character)->stat.Skills.Deception = temp;
    fscanf(fd, "%u\n", &temp);
    (*character)->stat.Skills.History = temp;
    fscanf(fd, "%u\n", &temp);
    (*character)->stat.Skills.Insight = temp;
    fscanf(fd, "%u\n", &temp);
    (*character)->stat.Skills.Intimidation = temp;
    fscanf(fd, "%u\n", &temp);
    (*character)->stat.Skills.Investigation = temp;
    fscanf(fd, "%u\n", &temp);
    (*character)->stat.Skills.Medicine = temp;
    fscanf(fd, "%u\n", &temp);
    (*character)->stat.Skills.Nature = temp;
    fscanf(fd, "%u\n", &temp);
    (*character)->stat.Skills.Perception = temp;
    fscanf(fd, "%u\n", &temp);
    (*character)->stat.Skills.Persuasion = temp;
    fscanf(fd, "%u\n", &temp);
    (*character)->stat.Skills.Religion = temp;
    fscanf(fd, "%u\n", &temp);
    (*character)->stat.Skills.SleightOfHand = temp;
    fscanf(fd, "%u\n", &temp);
    (*character)->stat.Skills.Stealth = temp;
    fscanf(fd, "%u\n", &temp);
    (*character)->stat.Skills.Survival = temp;

    fscanf(fd, "%u\n", &((*character)->stat.Strength));
    fscanf(fd, "%u\n", &((*character)->stat.Dexterity));
    fscanf(fd, "%u\n", &((*character)->stat.Constitution));
    fscanf(fd, "%u\n", &((*character)->stat.Intelligence));
    fscanf(fd, "%u\n", &((*character)->stat.Wisdom));
    fscanf(fd, "%u\n", &((*character)->stat.Charisma));

    // Misc inv ints
    fscanf(fd, "%u\n", &((*character)->Inspiration));
    fscanf(fd, "%u\n", &((*character)->Proficiency));
    fscanf(fd, "%u\n", &((*character)->Initiative));
    fscanf(fd, "%u\n", &((*character)->Speed));
    fscanf(fd, "%u\n", &((*character)->ArmorClass));
    fscanf(fd, "%u\n", &((*character)->MaxHP));
    fscanf(fd, "%u\n", &((*character)->CurHP));
    fscanf(fd, "%u\n", &((*character)->TempHP));
    fscanf(fd, "%u\n", &((*character)->TotDice));
    fscanf(fd, "%u\n", &((*character)->HitDice));

    // Misc inv string arrays
    fscanf(fd, "%s\n", (*character)->Personality);

    fscanf(fd, "%s\n", (*character)->Ideals);
    
    fscanf(fd, "%s\n", (*character)->Bonds);
    
    fscanf(fd, "%s\n", (*character)->Flaws);

    // Attacks
    fscanf(fd, "%u\n", &temp);
    
    for (i = 0; i < temp; i++)
    {
        fscanf(fd, "%s\n", (*character)->Attacks[i].Name);
        fscanf(fd, "%u\n", &((*character)->Attacks[i].Atk));
        fscanf(fd, "%u\n", &((*character)->Attacks[i].Type));
    }
    fgetpos(fd, cur_pos);
    printf("Cur: %d, End: %d\n", cur_pos, char_end);

    /* if (cur_pos > char_end)
    {
        ret = BADCHAR;
        printf("%d\n", ret);
        goto fail;
    } */

    if(fd)
        fclose(fd);

    return ret;
exit:
    if (fd)
        fclose(fd);
    
    clean_char(character);

    return ret;
}

/*!
 * @brief Save a Character struct to a save file.
 * 
 * Primary function for saving character data to a save file.
 * Characters inventory and stats are saved according to the 
 * format in the profile.cht file.
 * 
 * @param[in] character Character struct containing all current character data
 *                      to save.
 * 
 * @returns	The function returns SUCCESS if there are no errors, otherwise it returns
 *          errors according to the standard.
 * 
 */
err write_char(Character character)
{
    err ret = SUCCESS;

exit:
    return ret;
}

uint create_char(Character character){}