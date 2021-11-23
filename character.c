#include "types.h"
#include "file.h"
#include "inventory.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

uint init_char(Character **character)
{
    char *locator;
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
    
    dat = malloc(64);
    if (dat == NULL)
    {
        perror("memory error");
        ret = MEMERROR;
        goto fail;
    }
    memset(dat, 0, 64);
    
    char_start = malloc(sizeof(fpos_t));
    if (char_start == NULL)
    {
        perror("memory error");
        ret = MEMERROR;
        goto fail;
    }
    memset(char_start, 0, sizeof(fpos_t));

    char_end = malloc(sizeof(fpos_t));
    if (char_end == NULL)
    {
        perror("memory error");
        ret = MEMERROR;
        goto fail;
    }
    memset(char_end, 0, sizeof(fpos_t));

    cur_pos = malloc(sizeof(fpos_t));
    if (cur_pos == NULL)
    {
        perror("memory error");
        ret = MEMERROR;
        goto fail;
    }
    memset(cur_pos, 0, sizeof(fpos_t));

    locator = malloc(64);
    if (locator == NULL)
    {
        perror("memory error");
        ret = MEMERROR;
        goto fail;
    }
    memset(locator, 0, 64);

    (*character) = malloc(sizeof(Character));
    if (character == NULL)
    {
        perror("memory error");
        ret = MEMERROR;
        goto fail;
    }
    memset((*character), 0, sizeof(Character));

    // Get character positions
    printf("Select identifier:");
    scanf("%s", locator);

    fd = fopen("profile.cht", "r");
    if (fd == NULL)
        goto fail;
    find_event(fd, char_start, char_end, locator);

    fsetpos(fd, char_start);
    // End character position

    ret = alloc_char(character);
    if (ret)
        goto fail;

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

    fclose(fd);

    return ret;
fail:
    if (fd)
        fclose(fd);
    
    clean_char(character);

    return ret;
}

uint write_char(Character character)
{
    uint ret = SUCCESS;

    return ret;
fail:
    return ret;
}

uint create_char(Character character){}