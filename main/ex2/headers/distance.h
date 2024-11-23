#include <string.h>
#include <stdlib.h>

/**
 * @brief Determine the minimum number of operations needed to trasform the string s2 into s1 (insertion and deletion)
 * @param s1 string you want to get
 * @param s2 string to transform
 * @return The minimum number of operations needed to trasform the string s2 into s1
 */
int edit_distance(const char *s1, const char* s2);

/**
 * @brief Determine the minimum number of operations needed to trasform the string s2 into s1 (insertion and deletion) with an optimization mechanism to avoid repeating the same steps multiple times
 * @param s1 string you want to get
 * @param s2 string to transform
 * @return The minimum number of operations needed to trasform the string s2 into s1
 */
int edit_distance_dyn(const char *s1, const char* s2);