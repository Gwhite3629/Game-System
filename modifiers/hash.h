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

static inline uint32_t
hash(char *string)
{
	unsigned long val = 5381;
	int c;
	while ((c = *string++)) {
		val = ((val << 5) + val) + c;
	}
	return (uint32_t)(val % (__INT_MAX__));
}

static inline int
cmp(const void *va, const void *vb)
{
	const hashmap_t *a = (const hashmap_t *)va;
	const hashmap_t *b = (const hashmap_t *)vb;
	return (int)(a->hash - b->hash);
}

static inline hashmap_t
raw_lookup(char *string, hashmap_t *user_table, int size)
{
	hashmap_t zero = {
		"None",
		0,
		NULL
	};
	uint32_t key = hash(string);
	hashmap_t table = {"None",key,NULL};
	hashmap_t *r = (hashmap_t *)bsearch(&table, user_table, size, sizeof(hashmap_t), &cmp);
	return r ? *r : zero;
}

static inline int
raw_insert(hashmap_t **map, int *size, char *string, void *data)
{
	int ret = SUCCESS;
    hashmap_t temp = raw_lookup(string, (*map), (*size));
    if (strcmp(temp.string, "None") != 0) {
        printf("String already in map32\n");
		printf("In map: %s\n", temp.string);
		printf("Lookup: %s\n", string);
        return 0;
    }

    (*size)++;
	alt((*map), (*size), hashmap_t);
	new((*map)[(*size)-1].string, strlen(string), char);
	strcpy((*map)[(*size)-1].string, string);
	(*map)[(*size)-1].data = data;
	(*map)[(*size)-1].hash = hash(string);
	qsort((*map), (*size), sizeof(hashmap_t), &cmp);

exit:
    return ret;
}

static inline int
raw_remove(hashmap_t **map, int *size, char *string)
{
	int ret = SUCCESS;

	hashmap_t temp = raw_lookup(string, (*map), (*size));
	hashmap_t *scan = (hashmap_t *)bsearch(&temp, (*map), (*size), sizeof(hashmap_t), &cmp);
	if (scan != NULL) {
		temp = (*map)[(*size)-1];
		(*map)[(*size)-1] = (*scan);
		(*scan) = temp;
		(*size)--;
		del(scan->string);
		alt((*map), (*size), hashmap_t);
	} else {
		printf("String not in map\n");
	}

exit:
	return ret;
}

typedef struct map {
	hashmap_t *raw_data;
	int size;
	map_lookup_f lookup;
	map_insert_f insert;
	map_remove_f remove;
} map_t;

static inline void *
map_lookup(void *m, char *string)
{
	return ((raw_lookup(string, ((map_t *)m)->raw_data, ((map_t *)m)->size)).data);
}

static inline int
map_insert(void *m, char *string, void *data)
{
	return raw_insert(&((map_t *)m)->raw_data, &((map_t *)m)->size, string, data);
}

static inline int
map_remove(void *m, char *string)
{
	return raw_remove(&((map_t *)m)->raw_data, &((map_t *)m)->size, string);
}

static inline int
map_init(map_t *m)
{
	int ret = SUCCESS;

	m->lookup = &map_lookup;
	m->insert = &map_insert;
	m->remove = &map_remove;

	new(m->raw_data, 1, hashmap_t);

	m->size = 0;

exit:
	return ret;
}

#endif // _HASH_H_