#include "../main/ex1/quick_sort.h"
#include "Unity/unity.h"

void test_null_array(void) {
    int *test = NULL;
    TEST_ASSERT_NULL(test);
    quick_sort(test, 0, 0, compare_int);
    TEST_ASSERT_NULL(test);
}

void test_empty_array(void) {
    int test[] = {};
    int expected = {};
    quick_sort(test, 0, 0, compare_int);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected. test, 0);
}

void test_positive_int_array() {
    int test[] = {14, 2, 97, 54, 11, 17, 34, 28, 55, 1, 22, 84, 5, 7, 222, 69, 152, 468, 874, 52};
    int expected[] = {1, 2, 5, 7, 11, 14, 17, 22, 28, 34, 52, 54, 55, 69, 84, 97, 152, 222, 468, 874};
    quick_sort(test, 20, sizeof(test[0]), compare_int);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, test, 20);
}

void test_negative_int_array(void) {
    int test[] = {-14, -2, -97, -54, -11, -17, -34, -28, -55, -1, -22, -84, -5, -7, -222, -69, -152, -468, -874, -52};
    int expected[] = {-874, -468, -222, -152, -97, -84, -69, -55, -54, -52, -34, -28, -22, -17, -14, -11, -7, -5, -2, -1};
    merge_sort(test, 20, sizeof(test[0]), compare_int);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, test, 20);
}

void test_int_array(void) {
    int test[] = {14, -2, 97, -54, 11, -17, 34, -28, 55, -1, 22, -84, 5, -7, 222, -69, 152, -468, 874, -52};
    int expected[] = {-468, -84, -69, -54, -52, -28, -17, -7, -2, -1, 5, 11, 14, 22, 34, 55, 97, 152, 222, 874};
    merge_sort(test, 20, sizeof(test[0]), compare_int);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, test, 20);
}

void test_float_array(void) {
    float test[] = {1.52f, 0.14f, 5.26f, 5.27f, 0.01f, 3.68f, 2.42f, 7.29f, 6.33f, 2.56f, 8.65f, 2.03f, 4.22f, 0.25f, 1.47f, 6.51f, 9.75f, 1.05f, 4.71f, 7.30f};
    float expected[] = {0.01f, 0.14f, 0.25f, 1.05f, 1.47f, 1.52f, 2.03f, 2.42f, 2.56f, 3.68f, 4.22f, 4.71f, 5.26f, 5.27f, 6.33f, 6.51f, 7.29f, 7.30f, 8.65f, 9.75f};
    merge_sort(test, 20, sizeof(test[0]), compare_float);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected, test, 20);
}

void test_double_array(void) {
    double test[] = {2.1689, 1.3514, 0.0000, 3.7536, 0.1579, 1.2477, 2.2222, 4.2874, 1.9863, 5.2478, 1.4876, 1.9967, 9.5672, 6.1804, 7.8912, 0.3721, 1.3462, 0.8743, 5.2198, 0.0024};
    double expected[] = {0.0000, 0.0024, 0.1579, 0.3721, 0.8743, 1.2477, 1.3462, 1.3514, 1.4876, 1.9863, 1.9967, 2.1689, 2.2222, 3.7536, 4.2874, 5.2198, 5.2478, 6.1804, 7.8912, 9.5672};
    merge_sort(test, 20, sizeof(test[0]), compare_double);
    TEST_ASSERT_EQUAL_DOUBLE_ARRAY(expected, test, 20);
}

void test_char_array(void) {
    char test[] = {'b', 'l', 'e', 'c', 'h', 'a', 'd', 'g', 'f', 'i', 'y', 'q', 'x', 's', 't', 'w', 'm', 'k', 'n', 'p'};
    char expected[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'k', 'l', 'm', 'n', 'p', 'q', 's', 't', 'w', 'x', 'y'};
    merge_sort(test, 20, sizeof(test[0]), compare_char);
    TEST_ASSERT_EQUAL_INT8_ARRAY(expected, test, 20);
}

void test_string_array(void) {
    char test[] = {"cg\0", "gc\0", "dr\0", "ae\0", "fm\0", "il\0", "hi\0", "bf\0", "eq\0", "la\0", "su\0", "me\0", "ca\0", "lo\0", "ag\0", "gh\0", "ta\0", "ma\0", "to\0", "ro\0", "du\0"};
    char expected[] = {"ae\0", "ag\0", "bf\0", "ca\0", "cg\0", "dr\0", "du\0", "eq\0", "fm\0", "gc\0", "gh\0", "hi\0", "il\0", "la\0", "lo\0", "ma\0", "me\0", "ro\0", "su\0", "ta\0", "to\0"};
    merge_sort(test, 20, sizeof(test[0]), compare_string);
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected, test, 20);
}

void test_already_sorted_array(void) {
    int test[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    merge_sort(test, 20, sizeof(test[0]), compare_int);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, test, 20);
}

void test_with_only_duplicated(void) {
    int test[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int expected[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    merge_sort(test, 20, sizeof(test[0]), compare_int);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, test, 20);
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