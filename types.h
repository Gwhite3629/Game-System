#ifndef _TYPES_H_
#define _TYPES_H_

#include <stdbool.h>
#include <stdint.h>
#include "types.h"

//! Unsigned int shortcut
#define uint unsigned int

/**
 * \defgroup ErrorCodes Return codes indicating status
 * @{
 */

/**
 * @brief Success return code
 * Indicates function has returned with no errors
 */
#define SUCCESS 0

/**
 * @brief Item error return code
 * Indicates function has encountered an error with an item type
 */
#define ITEMERR 1

/**
 * @brief Drop item error return code
 * Indicates function has encountered a problem with a dropped item
 */
#define DROPERR 2

/**
 * @brief View error return code
 * Indicates function has an error viewing an inventory. This suggests
 * inventory corruption.
 */
#define VIEWERR 3

/**
 * @brief No parameters return code
 * Indicates that no or insufficient parameters were given for a function.
 */
#define NOPARAM 4

/**
 * @brief Overflow prevention return code
 * Indicates that there was an attempt to overflow a full inventory or buffer
 */
#define WARNFULL 5

/**
 * @brief Memory error return code
 * Indicates a generic error with memory
 */
#define MEMERROR 6

/**
 * @brief Bad character return code
 * Indicates an error with a character.
 */
#define BADCHAR 7
/**@}*/

/*!
 * @brief Types of damage
 * 
 */
typedef enum DamageType{Magic, Melee, Ranged} DamageType;


/*!
 * @brief A struct containing an entities saving throws
 * 
 * Saving throws are minimum values needed on a dice roll to pass
 * a given interaction.
 * 
 * Example:
 *  A strength saving throw is used when a character needs to move an object
 */
typedef struct SavingThrows {
  uint Strength; //!< Strength saving throw
  uint Dexterity; //!< Dexterity saving throw
  uint Constitution; //!< Constitution saving throw
  uint Intelligence; //!< Intelligence saving throw
  uint Wisdom; //!< Wisdom saving throw
  uint Charisma; //!< Charisma saving throw
} SavingThrows;

/*!
 * @brief A struct containing an entities skills
 * 
 * This struct contains flags indicating if the character has the skill
 */
typedef struct Skills {
  bool Acrobatics; //!< Acrobatics flag
  bool AnimalHandling; //!< Animal Handling flag
  bool Arcana; //!< Arcana flag
  bool Athletics; //!< Athletics flag
  bool Deception; //!< Deception flag
  bool History; //!< History flag
  bool Insight; //!< Insight flag
  bool Intimidation; //!< Intimidation flag
  bool Investigation; //!< Investigation flag
  bool Medicine; //!< Medicine flag
  bool Nature; //!< Nature flag
  bool Perception; //!< Perception flag
  bool Persuasion; //!< Persuasion flag
  bool Religion; //!< Religion flag
  bool SleightOfHand; //!< Sleight of hand flag
  bool Stealth; //!< Stealth flag
  bool Survival; //!< Survival flag
} Skills;

/*!
 * @brief A struct that indicates an items type
 * 
 * Each item has a type, these can be generic or specific depending
 * on the item. Every item type has a name. Some items do not have all
 * attributes and therefore have 0 in the respective attribute.
 */
typedef struct Types {
  char *Name; //!< Name of the item type
  uint32_t Health; //!< Health of item
  uint32_t Damage; //!< Damage item does
  uint32_t Hunger; //!< Hunger item heals
  uint32_t Poison; //!< Poison item inflicts
  uint32_t Regen; //!< Regen item causes
} Type;

/*!
 * @brief A struct that defines an item
 * 
 * Each item has a struct defining its attributes such as name, description,
 * type and id. Position is also tracked to indicate if an error in inventory management
 * has occured. The item id flag is used to track generic items.
 */
typedef struct Items {
  char *Name; //!< Name of the item
  Type Type; //!< Item type
  char *Description; //!< Item description
  uint32_t id; //!< Item id, 0 if generic item
  uint8_t position; //!< Position of the item in an inventory
} Item;

/*!
 * @brief A struct that defines an inventory
 * 
 * Inventories are defined by an identifier and contain items. There are 32
 * slots in any inventory. Inventories have a state variable to indicate if they
 * are full, empty, busy, or in some other state.
 */
typedef struct Inventory {
  char *identity; //!< Unique name of inventory
  uint16_t state; //!< Inventory status, indicating full, empty, busy, etc.
  Item slots[32]; //!< Actual inventory storage
  uint8_t size; //!< Current size of inventory
  bool full[32]; //!< Bitmap indicating if a slot has an item or not
} Inv;

typedef uint16_t err;

/*!
 * @brief A struct that defines an attack
 * 
 * Attacks are defined by a name, damage amount, and damage type.
 * Damage values are before armor and regardless of attack type.
 * Types are used to calculate resistances and weaknesses.
 */
typedef struct Attack {
  char *Name; //!< Name of attack
  uint Atk; //!< Damage value
  DamageType Type; //!< Type of attack damage
} Attack;

/*!
 * @brief A struct that defines an entities stats
 * 
 * Stats are used for most interactions with the world. Most stats are used
 * to calculate an entities direct actions, and saving throws are used for
 * actions done to the entity. Skills are simple flags and the characters stats
 * indicate adeptness at those skills.
 */
typedef struct Stats {
  SavingThrows Save; //!< Throwing saves
  Skills Skills; //!< Skill flags
  uint Strength; //!< Strength stat
  uint Dexterity; //!< Dexterity stat
  uint Constitution; //!< Constitution stat
  uint Intelligence; //!< Intelligence stat
  uint Wisdom; //!< Wisdom stat
  uint Charisma; //!< Charisma stat
} Stats;

/*!
 * @brief A struct that defines a character
 * 
 * Characters are defined by many different structures. Each character has their
 * own unique inventory. Characters also have their own stats and attacks.
 * Stats can be improved and attacks can be learned and improved.
 * 
 * Variable stats are situation dependent and set depending on global environment changes
 * as well as challenges to their ideals and character bonds. These are determined dynamically
 * and changed with certain events defined elsewhere.
 * 
 * Speed and armor class are determined at character creation. Armor class can be changed depending on
 * certain training events. Speed is used to determine a characters ability to make sudden actions.
 * 
 * Maximum health points can be increased through potions, training, magic and other systems. Temporary
 * health points arise through external buffs or debuffs. Hit dice are the number of dice a character can roll
 * to determine damage in a turn. Dice are lost through tiring. Dice are recovered up to total dice through rest.
 * 
 * Personality, Ideals, Bonds, and Flaws are used to determine situational variables like character interactions 
 * and can cause bufs or debuffs. Personality is a simple description that other characters receive upon meeting.
 * Ideals determine a characters affinity to certain factions and other personality traits. Bonds determine 
 * other characters who grant buffs. Flaws indicate specific personality traits that can cause debuffs.
 */
typedef struct Character {
  Inv Inventory; //!< Characters inventory
  Stats stat; //!< Characters stats
  uint Inspiration; //!< Inspiration stat, variable
  uint Proficiency; //!< Proficiency stat, variable
  uint Initiative; //!< Initiative stat, variable
  uint Speed; //!< Speed stat, static
  uint ArmorClass; //!< Armor class
  uint MaxHP; //!< Current maximum health points
  uint CurHP; //!< Current health points
  uint TempHP; //!< Temporary health points
  uint TotDice; //!< Maximum number of attack dice
  uint HitDice; //!< Current number of attack dice
  char *Personality; //!< Personality description
  char *Ideals; //!< Ideals description
  char *Bonds; //!< Character bonds
  char *Flaws; //!< Character flaws
  Attack *Attacks; //!< Character attacks
} Character;

#endif // _TYPES_H_