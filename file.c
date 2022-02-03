/*!
 * @file file.c
 * 
 * @brief This function keeps track of file related events.
 * 
 * @author Grady White
 * 
 * @date 2/2/2022
 * 
 * Functions in this file are responsible for specific file operations
 * such as file searching, ordering, and concatenation.
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*!
 * @brief Searches a file for an event
 * 
 * This function searches through a file starting at the current file position
 * in the FILE stream sent. Once the event has been found its position is written
 * to the prof_start variable and once it has been found again the position
 * is written to prof_end. The locator variable is the event to compare against.
 * 
 * @param[in] fd The file to locate the event
 * 
 * @param[in,out] prof_start Position of event in file
 * @param[in,out] prof_end Second position of event in file
 * 
 * @param[out] locator Event to search for
 * 
 * @returns	The function returns SUCCESS if there are no errors, otherwise it returns
 *          errors according to the standard.
 * 
 */
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