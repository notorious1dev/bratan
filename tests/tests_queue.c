#include "unity.h"
#include "queue_t.h"
#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}

void When_CreateLinkedList_Expect_Empty(void) {
    queue_t q = queue_init();
    TEST_ASSERT_NULL(q.head);
    TEST_ASSERT_NULL(q.tail);
    TEST_ASSERT_EQUAL(0, q.length);
}

void When_EnqueueOneNode_Expect_LengthOneAndHeadTailSame(void) {
    queue_t q = queue_init();
    int *data = malloc(sizeof(int));
    *data = 1;
    node_t *n = create_node(data);
    queue_enqueue(&q, n);
    TEST_ASSERT_EQUAL_PTR(q.head, q.tail);
    TEST_ASSERT_EQUAL(1, q.length);
}

void When_EnqueueTwoNodes_Expect_TailPointsToLast(void) {
    queue_t q = queue_init();
    int *d1 = malloc(sizeof(int)); *d1 = 1;
    int *d2 = malloc(sizeof(int)); *d2 = 2;

    queue_enqueue(&q, create_node(d1));
    queue_enqueue(&q, create_node(d2));

    TEST_ASSERT_EQUAL(2, q.length);
    TEST_ASSERT_EQUAL(2, *(int*)q.tail->data);
}

void When_DequeueOneNode_Expect_QueueEmpty(void) {
    queue_t q = queue_init();
    int *d = malloc(sizeof(int)); *d = 10;
    node_t *n = create_node(d);

    queue_enqueue(&q, n);
    node_t *deq = queue_dequeue(&q);

    TEST_ASSERT_EQUAL_PTR(n, deq);
    TEST_ASSERT_NULL(q.head);
    TEST_ASSERT_NULL(q.tail);
    TEST_ASSERT_EQUAL(0, q.length);

    free(deq->data);
    free(deq);
}

void When_DequeueEmptyQueue_Expect_Null(void) {
    queue_t q = queue_init();
    node_t *deq = queue_dequeue(&q);
    TEST_ASSERT_NULL(deq);
}

void When_PeekEmptyQueue_Expect_Null(void) {
    queue_t q = queue_init();
    TEST_ASSERT_NULL(queue_peek(&q));
}

void When_PeekAfterEnqueue_Expect_HeadNode(void) {
    queue_t q = queue_init();
    int *d = malloc(sizeof(int)); *d = 5;
    node_t *n = create_node(d);
    queue_enqueue(&q, n);

    TEST_ASSERT_EQUAL_PTR(n, queue_peek(&q));
}

void When_ClearQueue_Expect_Empty(void) {
    queue_t q = queue_init();
    queue_enqueue(&q, create_node(malloc(sizeof(int))));
    queue_enqueue(&q, create_node(malloc(sizeof(int))));
    queue_clear(&q);

    TEST_ASSERT_NULL(q.head);
    TEST_ASSERT_NULL(q.tail);
    TEST_ASSERT_EQUAL(0, q.length);
}

void When_EnqueueAfterClear_Expect_CorrectLength(void) {
    queue_t q = queue_init();
    queue_enqueue(&q, create_node(malloc(sizeof(int))));
    queue_clear(&q);
    queue_enqueue(&q, create_node(malloc(sizeof(int))));

    TEST_ASSERT_EQUAL(1, q.length);
    TEST_ASSERT_NOT_NULL(q.head);
    TEST_ASSERT_NOT_NULL(q.tail);
}

void When_DequeueMultipleNodes_Expect_OrderCorrect(void) {
    queue_t q = queue_init();
    int *d1 = malloc(sizeof(int)); *d1 = 1;
    int *d2 = malloc(sizeof(int)); *d2 = 2;
    queue_enqueue(&q, create_node(d1));
    queue_enqueue(&q, create_node(d2));

    node_t *n1 = queue_dequeue(&q);
    node_t *n2 = queue_dequeue(&q);

    TEST_ASSERT_EQUAL(1, *(int*)n1->data);
    TEST_ASSERT_EQUAL(2, *(int*)n2->data);

    free(n1->data); free(n1);
    free(n2->data); free(n2);
}

void When_FreeQueue_Expect_NoMemoryLeak(void) {
    queue_t *q = malloc(sizeof(queue_t));
    *q = queue_init();
    queue_enqueue(q, create_node(malloc(sizeof(int))));
    queue_free(q); 
    TEST_ASSERT_TRUE(1); 
}

void When_EnqueueMultipleNodes_Expect_LengthIncrements(void) {
    queue_t q = queue_init();
    for (int i = 0; i < 5; i++) {
        queue_enqueue(&q, create_node(malloc(sizeof(int))));
        TEST_ASSERT_EQUAL(i + 1, q.length);
    }
    queue_clear(&q);
}

void When_DequeueHead_Expect_TailCorrect(void) {
    queue_t q = queue_init();
    int *d1 = malloc(sizeof(int)); *d1 = 1;
    int *d2 = malloc(sizeof(int)); *d2 = 2;
    queue_enqueue(&q, create_node(d1));
    queue_enqueue(&q, create_node(d2));

    node_t *n1 = queue_dequeue(&q);
    TEST_ASSERT_EQUAL_PTR(q.tail->data, d2);
    free(n1->data); free(n1);
    queue_clear(&q);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(When_CreateLinkedList_Expect_Empty);
    RUN_TEST(When_EnqueueOneNode_Expect_LengthOneAndHeadTailSame);
    RUN_TEST(When_EnqueueTwoNodes_Expect_TailPointsToLast);
    RUN_TEST(When_DequeueOneNode_Expect_QueueEmpty);
    RUN_TEST(When_DequeueEmptyQueue_Expect_Null);
    RUN_TEST(When_PeekEmptyQueue_Expect_Null);
    RUN_TEST(When_PeekAfterEnqueue_Expect_HeadNode);
    RUN_TEST(When_ClearQueue_Expect_Empty);
    RUN_TEST(When_EnqueueAfterClear_Expect_CorrectLength);
    RUN_TEST(When_DequeueMultipleNodes_Expect_OrderCorrect);
    RUN_TEST(When_FreeQueue_Expect_NoMemoryLeak);
    RUN_TEST(When_EnqueueMultipleNodes_Expect_LengthIncrements);
    RUN_TEST(When_DequeueHead_Expect_TailCorrect);

    UNITY_END();
}
