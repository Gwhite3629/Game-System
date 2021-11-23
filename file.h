#ifndef _FILE_H_
#define _FILE_H_

#include <stdio.h>

int find_event(FILE *fd, fpos_t *char_start, fpos_t *char_end, char *locator);

#endif // _FILE_H_