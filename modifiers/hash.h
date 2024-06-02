#ifndef _HASH_H_
#define _HASH_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "utils.h"
#include "memory.h"

typedef void * (*map_lookup_f)(void *, char *);
typedef int    (*map_insert_f)(void *, char *, void *);
typedef int    (*map_remove_f)(void *, char *);

typedef struct hashmap_t {
    char *string;
    uint32_t hash;
	void *data;
} hashmap_t;

typedef struct map {
	hashmap_t *raw_data;
	int size;
	map_lookup_f lookup;
	map_insert_f insert;
	map_remove_f remove;
} map_t;

int map_init(map_t *m);

void *map_lookup(void *m, char *string);

int map_insert(void *m, char *string, void *data);

int map_remove(void *m, char *string);

#endif // _HASH_H_