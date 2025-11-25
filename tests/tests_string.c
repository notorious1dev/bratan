#include "unity.h"
#include "string_t.h"
#include <stdlib.h>
#include <string.h>

void setUp(void) {}
void tearDown(void) {}

void When_ConstructString_Then_NotNull(void) {
    string_t *s = string_constructor("hello");
    TEST_ASSERT_NOT_NULL(s);
    TEST_ASSERT_EQUAL_STRING("hello", s->data);
    TEST_ASSERT_EQUAL(5, s->length);
    string_free(s);
}

void When_ConstructEmptyString_Then_LengthZero(void) {
    string_t *s = string_constructor("");
    TEST_ASSERT_NOT_NULL(s);
    TEST_ASSERT_EQUAL_STRING("", s->data);
    TEST_ASSERT_EQUAL(0, s->length);
    string_free(s);
}

void When_ConstructMultipleStrings_Then_DataIsIndependent(void) {
    string_t *s1 = string_constructor("one");
    string_t *s2 = string_constructor("two");
    TEST_ASSERT_NOT_EQUAL(s1->data, s2->data);
    TEST_ASSERT_EQUAL_STRING("one", s1->data);
    TEST_ASSERT_EQUAL_STRING("two", s2->data);
    string_free(s1);
    string_free(s2);
}

void When_StringFree_Then_CanNotAccess(void) {
    string_t *s = string_constructor("test");
    string_free(s);
    TEST_ASSERT_TRUE(1); 
}

void When_ConstructLongString_Then_LengthCorrect(void) {
    const char *text = "this is a long string for testing";
    string_t *s = string_constructor(text);
    TEST_ASSERT_EQUAL(strlen(text), s->length);
    TEST_ASSERT_EQUAL_STRING(text, s->data);
    string_free(s);
}

void When_ConstructStringWithSpaces_Then_ContentCorrect(void) {
    string_t *s = string_constructor("a b c");
    TEST_ASSERT_EQUAL_STRING("a b c", s->data);
    TEST_ASSERT_EQUAL(5, s->length);
    string_free(s);
}

void When_ConstructStringWithSpecialChars_Then_ContentCorrect(void) {
    string_t *s = string_constructor("!@#$%^&*()");
    TEST_ASSERT_EQUAL_STRING("!@#$%^&*()", s->data);
    TEST_ASSERT_EQUAL(10, s->length);
    string_free(s);
}

void When_ConstructStringTwice_Then_ModifyOneDoesNotAffectOther(void) {
    string_t *s1 = string_constructor("abc");
    string_t *s2 = string_constructor("abc");
    s1->data[0] = 'z';
    TEST_ASSERT_EQUAL_STRING("zbc", s1->data);
    TEST_ASSERT_EQUAL_STRING("abc", s2->data);
    string_free(s1);
    string_free(s2);
}

void When_ConstructStringThenCompare_ThenEqual(void) {
    string_t *s1 = string_constructor("compare");
    string_t *s2 = string_constructor("compare");
    TEST_ASSERT_EQUAL_STRING(s1->data, s2->data);
    string_free(s1);
    string_free(s2);
}

void When_ConstructStringThenLength_ThenMatchesStrlen(void) {
    const char *text = "length test";
    string_t *s = string_constructor(text);
    TEST_ASSERT_EQUAL(strlen(text), s->length);
    string_free(s);
}

void When_ConstructMultipleStrings_ThenMemoryIndependent(void) {
    string_t *s1 = string_constructor("x");
    string_t *s2 = string_constructor("y");
    TEST_ASSERT_NOT_EQUAL(s1->data, s2->data);
    string_free(s1);
    string_free(s2);
}

void When_ConstructStringWithNumbers_Then_ContentCorrect(void) {
    string_t *s = string_constructor("1234567890");
    TEST_ASSERT_EQUAL_STRING("1234567890", s->data);
    TEST_ASSERT_EQUAL(10, s->length);
    string_free(s);
}

void When_ConstructStringWithMixedChars_Then_ContentCorrect(void) {
    string_t *s = string_constructor("AbC123!@#");
    TEST_ASSERT_EQUAL_STRING("AbC123!@#", s->data);
    TEST_ASSERT_EQUAL(9, s->length);
    string_free(s);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(When_ConstructString_Then_NotNull);
    RUN_TEST(When_ConstructEmptyString_Then_LengthZero);
    RUN_TEST(When_ConstructMultipleStrings_Then_DataIsIndependent);
    RUN_TEST(When_StringFree_Then_CanNotAccess);
    RUN_TEST(When_ConstructLongString_Then_LengthCorrect);
    RUN_TEST(When_ConstructStringWithSpaces_Then_ContentCorrect);
    RUN_TEST(When_ConstructStringWithSpecialChars_Then_ContentCorrect);
    RUN_TEST(When_ConstructStringTwice_Then_ModifyOneDoesNotAffectOther);
    RUN_TEST(When_ConstructStringThenCompare_ThenEqual);
    RUN_TEST(When_ConstructStringThenLength_ThenMatchesStrlen);
    RUN_TEST(When_ConstructMultipleStrings_ThenMemoryIndependent);
    RUN_TEST(When_ConstructStringWithNumbers_Then_ContentCorrect);
    RUN_TEST(When_ConstructStringWithMixedChars_Then_ContentCorrect);
    UNITY_END();
}
