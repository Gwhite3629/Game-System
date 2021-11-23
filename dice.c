#include "types.h"
#include <stdlib.h>

uint *roll(uint num, uint sides)
{
    int i;
    uint *result = NULL;
    result = malloc(num * sizeof(uint));
    for (i=0; i<num; i++) {
        switch (sides) {
            case 4:
                result[i] = (rand() % 5);
                break;
            case 6:
                result[i] = (rand() % 7);
                break;
            case 8:
                result[i] = (rand() % 9);
                break;
            case 10:
                result[i] = (rand() % 11);
                break;
            case 12:
                result[i] = (rand() % 13);
                break;
            case 20:
                result[i] = (rand() % 21);
                break;
            default:
                free(result);
                return NOPARAM;
        }
    }
    return result;
}