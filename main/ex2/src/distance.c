#include "../headers/distance.h"

int edit_distance(const char *s1, const char* s2) {
    if (strlen(s1) == 0)
        return strlen(s2);

    if (strlen(s2) == 0)
        return strlen(s1);
    
    int d_noop = 0;
    
    if (s1[0] == s2[0])
        d_noop = edit_distance(s1 + 1, s2 + 1);
    else
        d_noop = __INT_MAX__;
    
    int d_canc = 1 + edit_distance(s1, s2 + 1);

    int d_ins = 1 + edit_distance(s1 + 1, s2);

    int min = d_noop;

    if (d_canc < min)
        min = d_canc;

    if (d_ins < min)
        min = d_ins;

    return min;
}