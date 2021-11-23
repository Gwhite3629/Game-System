#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int find_event(FILE *fd, fpos_t *prof_start, fpos_t *prof_end, char *locator)
{
  int flag = 0;
  int found = 0;
  char *buffer = NULL;

  buffer = malloc(strlen(locator));
  if (buffer == NULL) {
    perror("memory error");
    goto fail;
  }
  memset(buffer, 0, strlen(locator));
// Prepares check based on user input profile selection
// Iterates through file and exits when it has found the start of the profile
  do {
    buffer[flag] = fgetc(fd);
    if (buffer[flag] == locator[flag]) {
      if (flag == strlen(locator)-1) {
        if (found == 0)
          fgetpos(fd, prof_start);
        else
          fgetpos(fd, prof_end);
        found++;
        flag=0;
      } else {
        flag++;
      }
    } else {
      flag = 0;
    }
    // if (flag > 0)
      // printf("buffer[flag]: %c, locator[flag]: %c, strlen(locator): %I64d, flag: %d, found: %d\n", buffer[flag], locator[flag], strlen(locator), flag, found);
  } while (found < 2);

  free(buffer);
  return 0;

fail:
  free(buffer);
  return -1;
}