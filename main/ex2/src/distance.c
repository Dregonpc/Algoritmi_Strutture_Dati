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

int edit_distance_dyn_rec(const char *s1, const char* s2, int **matrix, int len1, int len2) {
    if (matrix[len1][len2] != -1) 
        return matrix[len1][len2];
    
    if (len1 == 0) {
        matrix[len1][len2] = len2;
        return matrix[len1][len2];
    }

    if (len2 == 0) {
        matrix[len1][len2] = len1;
        return matrix[len1][len2];
    }

    int d_noop = 0;
    
    if (s1[0] == s2[0])
        d_noop = edit_distance_dyn_rec(s1 + 1, s2 + 1, matrix, len1 - 1, len2 - 1);
    else
        d_noop = __INT_MAX__;

    int d_canc = 1 + edit_distance_dyn_rec(s1, s2 + 1, matrix, len1, len2 - 1);

    int d_ins = 1 + edit_distance_dyn_rec(s1 + 1, s2, matrix, len1 - 1, len2);

    int min = d_noop;

    if (d_canc < min)
        min = d_canc;

    if (d_ins < min)
        min = d_ins;

    matrix[len1][len2] = min;

    return matrix[len1][len2];
}

int edit_distance_dyn(const char *s1, const char* s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);

    int **matrix = (int **)malloc((len1 + 1) * sizeof(int *));
    for (int r = 0; r <= len1; r++) {
        matrix[r] = (int *)malloc((len2 + 1) * sizeof(int *));
        for (int c = 0; c <= len2; c++) {
            matrix[r][c] = -1;
        }
    }
    
    int result = edit_distance_dyn_rec(s1, s2, matrix, len1, len2);

    for (int r = 0; r <= len1; r++) {
        free(matrix[r]);
    }
    free(matrix);

    return result;
}