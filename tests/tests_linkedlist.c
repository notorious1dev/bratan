#include "unity.h"
#include "linkedlist_t.h"
#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}

void When_CreateLinkedList_Then_ListIsEmpty(void) {
    linkedlist_t ll = create_linkedlist();
    TEST_ASSERT_NULL(ll.head);
    TEST_ASSERT_EQUAL(0, ll.length);
}

void When_AddNode_Then_HeadIsNode(void) {
    linkedlist_t ll = create_linkedlist();
    int *data = malloc(sizeof(int)); *data = 10;
    node_t *n = create_node(data);
    add_node(&ll, n);
    TEST_ASSERT_EQUAL_PTR(n, ll.head);
    TEST_ASSERT_EQUAL(1, ll.length);
}

void When_AddMultipleNodes_Then_HeadIsLastAdded(void) {
    linkedlist_t ll = create_linkedlist();
    int *d1 = malloc(sizeof(int)); *d1 = 1;
    int *d2 = malloc(sizeof(int)); *d2 = 2;
    node_t *n1 = create_node(d1);
    node_t *n2 = create_node(d2);
    add_node(&ll, n1);
    add_node(&ll, n2);
    TEST_ASSERT_EQUAL_PTR(n2, ll.head);
    TEST_ASSERT_EQUAL(2, ll.length);
}

void When_AppendNodeToEmptyList_Then_HeadIsNode(void) {
    linkedlist_t ll = create_linkedlist();
    int *data = malloc(sizeof(int)); *data = 5;
    node_t *n = create_node(data);
    append_node(&ll, n);
    TEST_ASSERT_EQUAL_PTR(n, ll.head);
    TEST_ASSERT_EQUAL(1, ll.length);
}

void When_AppendNodeToNonEmptyList_Then_TailIsNode(void) {
    linkedlist_t ll = create_linkedlist();
    int *d1 = malloc(sizeof(int)); *d1 = 1;
    int *d2 = malloc(sizeof(int)); *d2 = 2;
    node_t *n1 = create_node(d1);
    node_t *n2 = create_node(d2);
    add_node(&ll, n1);
    append_node(&ll, n2);
    node_t *temp = ll.head;
    while (temp->next != NULL) temp = temp->next;
    TEST_ASSERT_EQUAL_PTR(n2, temp);
    TEST_ASSERT_EQUAL(2, ll.length);
}

void When_DeleteHeadNode_Then_HeadPointsNext(void) {
    linkedlist_t ll = create_linkedlist();
    int *d1 = malloc(sizeof(int)); *d1 = 1;
    int *d2 = malloc(sizeof(int)); *d2 = 2;
    node_t *n1 = create_node(d1);
    node_t *n2 = create_node(d2);
    add_node(&ll, n1);
    append_node(&ll, n2);
    delete_node(&ll, n1);
    TEST_ASSERT_EQUAL_PTR(n2, ll.head);
    TEST_ASSERT_EQUAL(1, ll.length);
}

void When_DeleteMiddleNode_Then_PreviousNextPointsNext(void) {
    linkedlist_t ll = create_linkedlist();
    int *d1 = malloc(sizeof(int)); *d1 = 1;
    int *d2 = malloc(sizeof(int)); *d2 = 2;
    int *d3 = malloc(sizeof(int)); *d3 = 3;
    node_t *n1 = create_node(d1);
    node_t *n2 = create_node(d2);
    node_t *n3 = create_node(d3);
    add_node(&ll, n1);
    append_node(&ll, n2);
    append_node(&ll, n3);
    delete_node(&ll, n2);
    TEST_ASSERT_EQUAL_PTR(n3, n1->next);
    TEST_ASSERT_EQUAL(2, ll.length);
}

void When_DeleteLastNode_Then_PreviousNextIsNull(void) {
    linkedlist_t ll = create_linkedlist();
    int *d1 = malloc(sizeof(int)); *d1 = 1;
    int *d2 = malloc(sizeof(int)); *d2 = 2;
    node_t *n1 = create_node(d1);
    node_t *n2 = create_node(d2);
    add_node(&ll, n1);
    append_node(&ll, n2);
    delete_node(&ll, n2);
    TEST_ASSERT_NULL(n1->next);
    TEST_ASSERT_EQUAL(1, ll.length);
}

void When_ResetLinkedList_Then_ListIsEmpty(void) {
    linkedlist_t ll = create_linkedlist();
    add_node(&ll, create_node(malloc(sizeof(int))));
    append_node(&ll, create_node(malloc(sizeof(int))));
    reset_linkedlist(&ll);
    TEST_ASSERT_NULL(ll.head);
    TEST_ASSERT_EQUAL(0, ll.length);
}

void When_FreeLinkedList_Then_NoCrash(void) {
    linkedlist_t *ll = malloc(sizeof(linkedlist_t));
    *ll = create_linkedlist();
    add_node(ll, create_node(malloc(sizeof(int))));
    free_linkedlist(ll);
    TEST_ASSERT_TRUE(1);
}

void When_CreateNodeWithData_Then_NodeHasData(void) {
    int *data = malloc(sizeof(int)); *data = 99;
    node_t *n = create_node(data);
    TEST_ASSERT_EQUAL_PTR(data, n->data);
    TEST_ASSERT_NULL(n->next);
    free(n->data);
    free(n);
}

void When_AddNodeThenAppendNode_Then_OrderIsCorrect(void) {
    linkedlist_t ll = create_linkedlist();
    int *d1 = malloc(sizeof(int)); *d1 = 1;
    int *d2 = malloc(sizeof(int)); *d2 = 2;
    node_t *n1 = create_node(d1);
    node_t *n2 = create_node(d2);
    add_node(&ll, n1);
    append_node(&ll, n2);
    TEST_ASSERT_EQUAL_PTR(n1->next, n2);
    TEST_ASSERT_EQUAL(2, ll.length);
}

void When_DeleteNonExistentNode_Then_ListUnchanged(void) {
    linkedlist_t ll = create_linkedlist();
    node_t *n1 = create_node(malloc(sizeof(int)));
    add_node(&ll, n1);
    node_t *fake = create_node(malloc(sizeof(int)));
    delete_node(&ll, fake);
    TEST_ASSERT_EQUAL_PTR(n1, ll.head);
    TEST_ASSERT_EQUAL(1, ll.length);
    free(fake->data);
    free(fake);
    reset_linkedlist(&ll);
}

void When_AddMultipleThenReset_Then_ListEmpty(void) {
    linkedlist_t ll = create_linkedlist();
    for (int i = 0; i < 5; i++) add_node(&ll, create_node(malloc(sizeof(int))));
    reset_linkedlist(&ll);
    TEST_ASSERT_NULL(ll.head);
    TEST_ASSERT_EQUAL(0, ll.length);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(When_CreateLinkedList_Then_ListIsEmpty);
    RUN_TEST(When_AddNode_Then_HeadIsNode);
    RUN_TEST(When_AddMultipleNodes_Then_HeadIsLastAdded);
    RUN_TEST(When_AppendNodeToEmptyList_Then_HeadIsNode);
    RUN_TEST(When_AppendNodeToNonEmptyList_Then_TailIsNode);
    RUN_TEST(When_DeleteHeadNode_Then_HeadPointsNext);
    RUN_TEST(When_DeleteMiddleNode_Then_PreviousNextPointsNext);
    RUN_TEST(When_DeleteLastNode_Then_PreviousNextIsNull);
    RUN_TEST(When_ResetLinkedList_Then_ListIsEmpty);
    RUN_TEST(When_FreeLinkedList_Then_NoCrash);
    RUN_TEST(When_CreateNodeWithData_Then_NodeHasData);
    RUN_TEST(When_AddNodeThenAppendNode_Then_OrderIsCorrect);
    RUN_TEST(When_DeleteNonExistentNode_Then_ListUnchanged);
    RUN_TEST(When_AddMultipleThenReset_Then_ListEmpty);
    UNITY_END();
}
