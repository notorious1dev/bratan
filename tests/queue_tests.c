#include "unity.h"
#include "unity_internals.h"
#include "queue_t.h"
#include <assert.h>

void setUp(void) {};
void tearDown(void) {};

void When_AddNode_Expect_HeadNotNull() {
    queue_t q = queue_init(&q);
    int * data = malloc(sizeof(int));
    *data = 5;
    node_t * n = create_node(data);
    queue_enqueue(&q, n);

    TEST_ASSERT_TRUE(q.head != NULL);
}

void When_AddNode_Expect_LenghtIncrement()
{
    queue_t q = queue_init(&q);
    
    for (int i = 0; i < 20; i++) {
        node_t * n = create_node(NULL);
        queue_enqueue(&q, n);
    }

    TEST_ASSERT_TRUE(q.length == 20);
}

void When_DequeueNode_Expect_LenghtDecrement()
{
    queue_t q = queue_init(&q);
    
    for (int i = 0; i < 20; i++) {
        node_t * n = create_node(NULL);
        queue_enqueue(&q, n);
    }

    for (int i = 0; i < 5; i ++)
    {
        node_t *n = queue_dequeue(&q);
    }

    TEST_ASSERT_TRUE(q.length == 15);
}

void When_PeekNotNullQueue_Expect_PeekNodeAndLenghtNotChanged()
{
    queue_t q = queue_init(&q);
    
    int * data = (int*)malloc(sizeof(int));
    *data = 5;
    node_t * n = create_node(data);
    queue_enqueue(&q, n);

    for (int i = 0; i < 5; i++) {
        node_t * n = create_node(NULL);
        queue_enqueue(&q, n);
    }

    node_t *f = queue_peek(&q);

    TEST_ASSERT_TRUE(q.length == 6);
    TEST_ASSERT_TRUE(*(int*)(f->data) == 5);
}

void When_FreeEmptyQueueOnHeap_Expect_NoCrash()
{
    queue_t * q = (queue_t*)malloc(sizeof(queue_t));
    queue_init(q);
    queue_free(q);
}

void When_ClearQueueOnHeap_Expect_NoCrash()
{
    queue_t * q = (queue_t*)malloc(sizeof(queue_t));
    queue_init(q);

    for (int i = 0; i < 20; i++) 
    {
        node_t * n = create_node(NULL);
        queue_enqueue(q, n);
    }

    queue_free(q);
}

void When_RepeatedEnqueueDequeue_Expect_StablePointers()
{
    queue_t q;
    queue_init(&q);

    for (int i = 0; i < 500; i++)
        queue_enqueue(&q, create_node(NULL));
    
    for (int i = 0; i < 499; i++)
        queue_dequeue(&q);

    TEST_ASSERT_NOT_NULL(q.head);
    TEST_ASSERT_NOT_NULL(q.tail);
    TEST_ASSERT_EQUAL_INT(1, q.length);
    TEST_ASSERT_EQUAL_PTR(q.head, q.tail);
}

void When_ManyOperations_Expect_CorrectLength()
{
    queue_t q;
    queue_init(&q);

    for (int i = 0; i < 10000; i++)
        queue_enqueue(&q, create_node(NULL));

    for (int i = 0; i < 9999; i++)
        queue_dequeue(&q);

    TEST_ASSERT_EQUAL_INT(1, q.length);
}

void When_ClearQueue_Expect_HeadTailNull()
{
    queue_t q;
    queue_init(&q);

    for (int i = 0; i < 5; i++)
        queue_enqueue(&q, create_node(NULL));

    queue_clear(&q);

    TEST_ASSERT_NULL(q.head);
    TEST_ASSERT_NULL(q.tail);
    TEST_ASSERT_EQUAL_INT(0, q.length);
}

void When_PeekEmptyQueue_Expect_NULL()
{
    queue_t q;
    queue_init(&q);

    node_t *n = queue_peek(&q);

    TEST_ASSERT_NULL(n);
}

void When_EnqueueMultiple_Expect_FIFO()
{
    queue_t q;
    queue_init(&q);

    int *a = malloc(sizeof(int)); *a = 1;
    int *b = malloc(sizeof(int)); *b = 2;
    int *c = malloc(sizeof(int)); *c = 3;

    queue_enqueue(&q, create_node(a));
    queue_enqueue(&q, create_node(b));
    queue_enqueue(&q, create_node(c));

    TEST_ASSERT_EQUAL_INT(1, *(int*)queue_dequeue(&q)->data);
    TEST_ASSERT_EQUAL_INT(2, *(int*)queue_dequeue(&q)->data);
    TEST_ASSERT_EQUAL_INT(3, *(int*)queue_dequeue(&q)->data);
}

void When_EnqueueFirstNode_Expect_HeadEqualsTail()
{
    queue_t q;
    queue_init(&q);

    node_t *n = create_node(NULL);
    queue_enqueue(&q, n);

    TEST_ASSERT_EQUAL_PTR(q.head, q.tail);
    TEST_ASSERT_EQUAL_INT(1, q.length);
}

void When_InitQueue_Expect_DefaultValues()
{
    queue_t q;
    queue_init(&q);

    TEST_ASSERT_NULL(q.head);
    TEST_ASSERT_NULL(q.tail);
    TEST_ASSERT_EQUAL_INT(0, q.length);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(When_AddNode_Expect_HeadNotNull);
    RUN_TEST(When_AddNode_Expect_LenghtIncrement);
    RUN_TEST(When_DequeueNode_Expect_LenghtDecrement);
    RUN_TEST(When_PeekNotNullQueue_Expect_PeekNodeAndLenghtNotChanged);
    RUN_TEST(When_FreeEmptyQueueOnHeap_Expect_NoCrash);
    RUN_TEST(When_ClearQueueOnHeap_Expect_NoCrash);
    RUN_TEST(When_RepeatedEnqueueDequeue_Expect_StablePointers);
    RUN_TEST(When_ManyOperations_Expect_CorrectLength);
    RUN_TEST(When_ClearQueue_Expect_HeadTailNull);
    RUN_TEST(When_PeekEmptyQueue_Expect_NULL);
    RUN_TEST(When_EnqueueMultiple_Expect_FIFO);
    RUN_TEST(When_EnqueueFirstNode_Expect_HeadEqualsTail);
    RUN_TEST(When_InitQueue_Expect_DefaultValues);
    UNITY_END();
}