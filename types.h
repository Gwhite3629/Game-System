#ifndef _TYPES_H_
#define _TYPES_H_

#include <stdbool.h>
#include <stdint.h>
#include "types.h"

#define uint unsigned int

#define SUCCESS 0
#define ITEMERR 1
#define DROPERR 2
#define VIEWERR 3
#define NOPARAM 4
#define WARNFULL 5
#define MEMERROR 6
#define BADCHAR 7

typedef enum DamageType{Magic, Melee, Ranged} DamageType;

typedef struct SavingThrows {
  uint Strength;
  uint Dexterity;
  uint Constitution;
  uint Intelligence;
  uint Wisdom;
  uint Charisma;
} SavingThrows;

typedef struct Skills {
  bool Acrobatics;
  bool AnimalHandling;
  bool Arcana;
  bool Athletics;
  bool Deception;
  bool History;
  bool Insight;
  bool Intimidation;
  bool Investigation;
  bool Medicine;
  bool Nature;
  bool Perception;
  bool Persuasion;
  bool Religion;
  bool SleightOfHand;
  bool Stealth;
  bool Survival;
} Skills;

typedef struct Types {
  char *Name;
  uint32_t Health;
  uint32_t Damage;
  uint32_t Hunger;
  uint32_t Poison;
  uint32_t Regen;
} Type;

typedef struct Items {
  char *Name;
  Type Type;
  char *Description;
  uint32_t id;
  uint8_t position;
} Item;

typedef struct Inventory {
  char *identity;
  uint16_t state;
  Item slots[32];
  uint8_t size;
  bool full[32];
} Inv;

typedef uint16_t err;

typedef struct Attack {
  char *Name;
  uint Atk;
  DamageType Type;
} Attack;

typedef struct Stats {
  SavingThrows Save;
  Skills Skills;
  uint Strength;
  uint Dexterity;
  uint Constitution;
  uint Intelligence;
  uint Wisdom;
  uint Charisma;
} Stats;

typedef struct Character {
  Inv Inventory;
  Stats stat;
  uint Inspiration;
  uint Proficiency;
  uint Initiative;
  uint Speed;
  uint ArmorClass;
  uint MaxHP;
  uint CurHP;
  uint TempHP;
  uint TotDice;
  uint HitDice;
  char *Personality;
  char *Ideals;
  char *Bonds;
  char *Flaws;
  Attack *Attacks;
} Character;

#endif // _TYPES_H_