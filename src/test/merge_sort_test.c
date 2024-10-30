#include "../ex1/merge_sort.h"
#include "Unity/unity.h"

void test_null_array(void) {
    int *test = NULL;
    TEST_ASSERT_NULL(test);
    merge_sort(test, 0, 0, compare_int);
    TEST_ASSERT_NULL(test);
}

void test_positive_int_array(void) {
    int test[] = {14, 2, 97, 54, 11, 17, 34, 28, 55, 1};
    int expected[] = {1, 2, 11, 14, 17, 28, 34, 54, 55, 97};
    merge_sort(test, 10, sizeof(test[0]), compare_int);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, test, 10);
}

void test_negative_int_array(void) {
    int test[] = {-14, -2, -97, -54, -11, -17, -34, -28, -55, -1};
    int expected[] = {-97, -55, -54, -34, -28, -17, -14, -11, -2, -1};
    merge_sort(test, 10, sizeof(test[0]), compare_int);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, test, 10);
}

void test_int_array(void) {
    int test[] = {14, -2, 97, -54, 11, -17, 34, -28, 55, 1};
    int expected[] = {-54, -28, -17, -2, 1, 11, 14, 34, 55, 97};
    merge_sort(test, 10, sizeof(test[0]), compare_int);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, test, 10);
}

void test_long_array(void) {
    
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_null_array);
    RUN_TEST(test_positive_int_array);
    RUN_TEST(test_negative_int_array);
    RUN_TEST(test_int_array);

    return UNITY_END();
}