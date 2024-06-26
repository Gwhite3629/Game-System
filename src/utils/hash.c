#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <utils/utils.h>
#include <utils/memory.h>
#include <utils/hash.h>

void print_map(hashmap_t *map, int size)
{
	printf("\n\n");
	printf("MAP DUMP:\n\t");
	for (int i = 0; i < size; i++) {
		printf("%s -> %d\n\t", map[i].string, map[i].hash);
	}
	printf("\n\n");
}

uint32_t hash(char *string)
{
	unsigned long val = 5381;
	int c;
	while ((c = *string++)) {
		val = ((val << 5) + val) + c;
	}
	return (uint32_t)(val % (__INT_MAX__));
}

int cmp(const void *va, const void *vb)
{
	const hashmap_t *a = (const hashmap_t *)va;
	const hashmap_t *b = (const hashmap_t *)vb;
	return (int)(a->hash - b->hash);
}

hashmap_t *raw_lookup(char *string, hashmap_t *user_table, int size)
{
	hashmap_t zero = {
		"None",
		0,
		0,
		NULL
	};
	uint32_t key = hash(string);
	hashmap_t table = {"None",key,0,NULL};
	hashmap_t *r = (hashmap_t *)bsearch(&table, user_table, size, sizeof(hashmap_t), &cmp);
	return r ? r : NULL;
}

int raw_insert(hashmap_t **map, int *size, char *string, void *data)
{
    hashmap_t *temp = raw_lookup(string, (*map), (*size));
    if (temp != NULL) {
        //printf("String already in map32\n");
		//printf("In map: %s\n", temp->string);
		//printf("Lookup: %s\n", string);

		temp->n_items++;
		alt(temp->data, temp->n_items+1, void *);
		temp->data[temp->n_items-1] = data;
		temp->data[temp->n_items] = NULL;
        return 0;
    }

    (*size)++;
	alt((*map), (*size), hashmap_t);
	new((*map)[(*size)-1].string, strlen(string)+1, char);
	strcpy((*map)[(*size)-1].string, string);
	(*map)[(*size)-1].string[strlen(string)] = '\0';
	(*map)[(*size)-1].n_items = 1;
	new((*map)[(*size)-1].data, 2, void *);
	(*map)[(*size)-1].data[0] = data;
	(*map)[(*size)-1].data[1] = NULL;
	(*map)[(*size)-1].hash = hash(string);
	qsort((*map), (*size), sizeof(hashmap_t), &cmp);
	//print_map((*map), (*size));

exit:
    return ret;
}

int raw_remove(hashmap_t **map, int *size, char *string)
{
	hashmap_t *temp = raw_lookup(string, (*map), (*size));
	if (temp == NULL) {
		return -1;
	}
	hashmap_t *scan = (hashmap_t *)bsearch(temp, (*map), (*size), sizeof(hashmap_t), &cmp);
	if (scan != NULL) {
		(*temp) = (*map)[(*size)-1];
		(*map)[(*size)-1] = (*scan);
		(*scan) = (*temp);
		(*size)--;
		del(scan->string);
		del(scan->data);
		alt((*map), (*size), hashmap_t);
	} else {
		printf("String not in map\n");
	}

exit:
	return ret;
}

void **map_lookup(void *m, char *string)
{
	hashmap_t *r = NULL;
	r = (raw_lookup(string, ((map_t *)m)->raw_data, ((map_t *)m)->size));
	return r ? r->data : NULL;
}

int map_insert(void *m, char *string, void *data)
{
	return raw_insert(&((map_t *)m)->raw_data, &((map_t *)m)->size, string, data);
}

int map_remove(void *m, char *string)
{
	return raw_remove(&((map_t *)m)->raw_data, &((map_t *)m)->size, string);
}

int map_init(map_t *m)
{
	m->lookup = &map_lookup;
	m->insert = &map_insert;
	m->remove = &map_remove;

	new(m->raw_data, 1, hashmap_t);

	m->size = 0;

exit:
	return ret;
}

// Returns NULL terminated list of pairs of data whose key
// Is the same between both maps. The pairs are ordered
// According to the key value and are in the sequence of
// [ref, dat], [ref, dat], where ref and dat are the corresponding
// Data from each map.
void ****map_union(map_t *ref, map_t *dat)
{
	void ****list = NULL;
	int list_size = 0;
	new(list, 1, void ***);
	new(list[0], 2, void **);
	char *rs1 = NULL;
	void *r1 = NULL;
	void *d1 = NULL;

	for (int i = 0; i < ref->size; i++) {
		rs1 = ref->raw_data[i].string;
		r1 = ref->lookup(ref, rs1);
		d1 = dat->lookup(dat, rs1);
		if (d1 != NULL) {
			list[list_size][0] = r1;
			list[list_size][1] = d1;
			list_size++;
			alt(list, list_size+1, void ***);
			new(list[list_size], 2, void **);
		}
	}

	list[list_size][0] = NULL;
	list[list_size][1] = NULL;

exit:
	return (ret == 0) ? list : NULL;
}
