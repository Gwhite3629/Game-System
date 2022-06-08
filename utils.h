#ifndef _UTILS_H_
#define _UTILS_H_

/**
 * \defgroup ErrorMessages Return messages for perror
 * @{
 */

/**
 * @brief Memory error code
 * Indicates a generic memory error
 */
#define MEM_CODE "memoryError"

/**
 * @brief File error code
 * Indicates a generic file error
 */
#define FILE_CODE "fileError"

/**@}*/

/**
 * \defgroup ErrorCodes Return codes indicating status
 * @{
 */

/**
 * @brief File open return code
 * Indicates that there was an issue openning a file
 */
#define FILE_OPEN -5

/**
 * @brief Miscellaneous return code
 * Indicates that there was an error somewhere in a function return
 */
#define BAD_ARGUMENT -4

/**
 * @brief No parameters return code
 * Indicates that no or insufficient parameters were given for a function.
 */
#define NO_PARAM -3

/**
 * @brief Thread error return code
 * Indicates that a thread returned an error
 */
#define THREAD_ERROR -2

/**
 * @brief Memory allocation return code
 * Indicates that memory allocation was not successful
 */
#define ALLOCATION_ERROR -1

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
 * @brief Overflow prevention return code
 * Indicates that there was an attempt to overflow a full inventory or buffer
 */
#define WARNFULL 4

/**
 * @brief Bad character return code
 * Indicates an error with a character.
 */
#define BADCHAR 5
/**@}*/

//  Memory or file check
#define VALID(check, code, err) \
    if ((check) == NULL) { \
        fprintf(stderr, "%s: %s\n", code, strerror(errno)); \
        perror(code); \
        ret = err; \
        goto exit; \
    }

#define HANDLE_ERR(check, code) \
    if (check != 0) { \
        fprintf(stderr, "%s: %s\n", code, strerror(errno)); \
        perror(code); \
        ret = THREAD_ERROR; \
        goto exit; \
    }

//  Memory alloc, checking, and allignment
#define MEM(ptr, size, type) \
    ptr = malloc(size*sizeof(type)); \
    VALID(ptr, MEM_CODE, ALLOCATION_ERROR); \
    memset(ptr, 0, size*sizeof(type));

//  Return condition check
#define CHECK(ret) \
    if ((ret) != 0) \
        goto exit;

#define CCHECK(c, s, v, err) \
    if (c s v) \
        ret = err; \
        goto exit;

#endif // _UTILS_H_