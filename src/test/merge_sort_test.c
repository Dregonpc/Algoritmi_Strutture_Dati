#include "../main/ex1/merge_sort.h"
#include "Unity/unity.h"

void test_null_array(void) {
    int *test = NULL;
    TEST_ASSERT_NULL(test);
    merge_sort(test, 0, 0, compare_int);
    TEST_ASSERT_NULL(test);
}

void test_empty_array(void) {
    int test[] = {};
    int expected[] = {};
    merge_sort(test, 0, 0, compare_int);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, test, 0);
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
    long test[] = {1423, 152, 759, 847, 10, 300, 635, 477, 852, 1256};
    long expected[] = {10, 152, 300, 477, 635, 759, 847, 852, 1256, 1423};
    merge_sort(test, 10, sizeof(test[0]), compare_long);
    TEST_ASSERT_EQUAL_INT32_ARRAY(expected, test, 10);
}

void test_float_array(void) {
    float test[] = {1.52f, 0.14f, 5.26f, 5.27f, 0.01f, 3.68f, 2.42f, 7.29f, 6.33f, 2.56f};
    float expected[] = {0.01f, 0.14f, 1.52f, 2.42f, 2.56f, 3.68f, 5.26f, 5.27f, 6.33f, 7.29f};
    merge_sort(test, 10, sizeof(test[0]), compare_float);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected, test, 10);
}

void test_double_array(void) {
    double test[] = {2.1689, 1.3514, 0.0000, 3.7536, 0.1579, 1.2477, 2.2222, 4.2874, 1.9863, 5.2478};
    double expected[] = {0.0000, 0.1579, 1.2477, 1.3514, 1.9863, 2.1689, 2.2222, 3.7536, 4.2874, 5.2478};
    merge_sort(test, 10, sizeof(test[0]), compare_double);
    TEST_ASSERT_EQUAL_DOUBLE_ARRAY(expected, test, 10);
}

void test_char_array(void) {
    char test[] = {'b', 'l', 'e', 'c', 'h', 'a', 'd', 'g', 'f', 'i'};
    char expected[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'l'};
    merge_sort(test, 10, sizeof(test[0]), compare_char);
    TEST_ASSERT_EQUAL_INT8_ARRAY(expected, test, 10);
}

void test_string_array(void) {
    char test[] = {"cg\0", "gc\0", "dr\0", "ae\0", "fm\0", "il\0", "hi\0", "bf\0", "eq\0", "la\0"};
    char expected[] = {"ae\0", "bf\0", "cg\0", "dr\0", "eq\0", "fm\0", "gc\0", "hi\0", "il\0", "la\0"};
    merge_sort(test, 10, sizeof(test[0]), compare_string);
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected, test, 10);
}

void test_already_sorted_array(void) {
    int test[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    merge_sort(test, 10, sizeof(test[0]), compare_int);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, test, 10);
}

void test_with_only_duplicated(void) {
    int test[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int expected[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    merge_sort(test, 10, sizeof(test[0]), compare_int);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, test, 10);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_null_array);
    RUN_TEST(test_empty_array);
    RUN_TEST(test_positive_int_array);
    RUN_TEST(test_negative_int_array);
    RUN_TEST(test_int_array);
    RUN_TEST(test_long_array);
    RUN_TEST(test_float_array);
    RUN_TEST(test_double_array);
    RUN_TEST(test_char_array);
    RUN_TEST(test_string_array);
    RUN_TEST(test_already_sorted_array);
    RUN_TEST(test_with_only_duplicated);

    return UNITY_END();
}