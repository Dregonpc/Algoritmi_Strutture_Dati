#include "../main/ex2/headers/distance.h"
#include "Unity/unity.h"

void setUp(void) {}
void tearDown(void) {}

void test_1(void) {
    char *s1 = "";
    char *s2 = "";
    TEST_ASSERT_EQUAL_INT(0, edit_distance(s1, s2));
}

void test_2(void) {
    char *s1 = "casa";
    char *s2 = "cassa";
    TEST_ASSERT_EQUAL_INT(1, edit_distance(s1, s2));
}

void test_3(void) {
    char *s1 = "casa";
    char *s2 = "cara";
    TEST_ASSERT_EQUAL_INT(2, edit_distance(s1, s2));
}

void test_4(void) {
    char *s1 = "vinaio";
    char *s2 = "vino";
    TEST_ASSERT_EQUAL_INT(2, edit_distance(s1, s2));
}

void test_5(void) {
    char *s1 = "tassa";
    char *s2 = "passato";
    TEST_ASSERT_EQUAL_INT(4, edit_distance(s1, s2));
}

void test_6(void) {
    char *s1 = "pioppo";
    char *s2 = "pioppo";
    TEST_ASSERT_EQUAL_INT(0, edit_distance(s1, s2));
}

void test_7(void) {
    char *s1 = "";
    char *s2 = "";
    TEST_ASSERT_EQUAL_INT(0, edit_distance_dyn(s1, s2));
}

void test_8(void) {
    char *s1 = "casa";
    char *s2 = "cassa";
    TEST_ASSERT_EQUAL_INT(1, edit_distance_dyn(s1, s2));
}

void test_9(void) {
    char *s1 = "casa";
    char *s2 = "cara";
    TEST_ASSERT_EQUAL_INT(2, edit_distance_dyn(s1, s2));
}

void test_10(void) {
    char *s1 = "vinaio";
    char *s2 = "vino";
    TEST_ASSERT_EQUAL_INT(2, edit_distance_dyn(s1, s2));
}

void test_11(void) {
    char *s1 = "tassa";
    char *s2 = "passato";
    TEST_ASSERT_EQUAL_INT(4, edit_distance_dyn(s1, s2));
}

void test_12(void) {
    char *s1 = "pioppo";
    char *s2 = "pioppo";
    TEST_ASSERT_EQUAL_INT(0, edit_distance_dyn(s1, s2));
}

int main(void) {
    UNITY_BEGIN();

    printf("\nEdit_distance() tests:\n\n");

    RUN_TEST(test_1);
    RUN_TEST(test_2);
    RUN_TEST(test_3);
    RUN_TEST(test_4);
    RUN_TEST(test_5);
    RUN_TEST(test_6);

    printf("\nEdit_distance_dyn() tests:\n\n");

    RUN_TEST(test_7);
    RUN_TEST(test_8);
    RUN_TEST(test_9);
    RUN_TEST(test_10);
    RUN_TEST(test_11);
    RUN_TEST(test_12);

    return UNITY_END();
}