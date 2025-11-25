#include "unity.h"
#include "threadpool_t.h"
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

volatile int counter = 0;

void* increment_counter(void* arg) {
    int *value = (int*)arg;
    __sync_fetch_and_add(&counter, *value);
    return NULL;
}

void setUp(void) { counter = 0; }
void tearDown(void) {}

void When_ThreadpoolInit_Then_NotNull(void) {
    threadpool_t *tp = threadpool_init(2);
    TEST_ASSERT_NOT_NULL(tp);
}

void When_ThreadpoolCreateSingleJob_Then_CounterIncremented(void) {
    threadpool_t *tp = threadpool_init(2);
    int val = 1;
    threadpool_create_work(tp, &val, increment_counter);
    sleep(1);
    TEST_ASSERT_EQUAL(1, counter);
}

void When_ThreadpoolCreateMultipleJobs_Then_CounterIncrementedCorrectly(void) {
    threadpool_t *tp = threadpool_init(3);
    int vals[5] = {1,1,1,1,1};
    for(int i=0;i<5;i++) threadpool_create_work(tp, &vals[i], increment_counter);
    sleep(2);
    TEST_ASSERT_EQUAL(5, counter);
}

void When_ThreadpoolMultipleThreads_Then_AllJobsExecuted(void) {
    threadpool_t *tp = threadpool_init(4);
    int vals[4] = {1,1,1,1};
    for(int i=0;i<4;i++) threadpool_create_work(tp, &vals[i], increment_counter);
    sleep(2);
    TEST_ASSERT_EQUAL(4, counter);
}

void When_ThreadpoolJobWithZeroValue_Then_CounterUnchanged(void) {
    threadpool_t *tp = threadpool_init(2);
    int val = 0;
    threadpool_create_work(tp, &val, increment_counter);
    sleep(1);
    TEST_ASSERT_EQUAL(0, counter);
}

void When_ThreadpoolSequentialJobs_Then_CounterIncrementedSequentially(void) {
    threadpool_t *tp = threadpool_init(2);
    int vals[3] = {1,2,3};
    for(int i=0;i<3;i++) threadpool_create_work(tp, &vals[i], increment_counter);
    sleep(2);
    TEST_ASSERT_EQUAL(6, counter);
}

void When_ThreadpoolManyJobs_Then_AllExecuted(void) {
    threadpool_t *tp = threadpool_init(3);
    int vals[10];
    for(int i=0;i<10;i++) { vals[i]=1; threadpool_create_work(tp, &vals[i], increment_counter);}
    sleep(3);
    TEST_ASSERT_EQUAL(10, counter);
}

void When_ThreadpoolSingleThread_Then_AllJobsExecuted(void) {
    threadpool_t *tp = threadpool_init(1);
    int vals[3]={1,1,1};
    for(int i=0;i<3;i++) threadpool_create_work(tp, &vals[i], increment_counter);
    sleep(3);
    TEST_ASSERT_EQUAL(3, counter);
}

void When_ThreadpoolCreateJobMultipleThreads_Then_AllThreadsWork(void) {
    threadpool_t *tp = threadpool_init(5);
    int vals[5]={1,1,1,1,1};
    for(int i=0;i<5;i++) threadpool_create_work(tp, &vals[i], increment_counter);
    sleep(3);
    TEST_ASSERT_EQUAL(5, counter);
}

void When_ThreadpoolNoJobs_Then_CounterZero(void) {
    threadpool_t *tp = threadpool_init(2);
    sleep(1);
    TEST_ASSERT_EQUAL(0, counter);
}

void When_ThreadpoolJobWithNegativeValue_Then_CounterDecremented(void) {
    threadpool_t *tp = threadpool_init(2);
    int val = -3;
    threadpool_create_work(tp, &val, increment_counter);
    sleep(1);
    TEST_ASSERT_EQUAL(-3, counter);
}

void When_ThreadpoolMultipleJobsMixedValues_Then_CounterCorrect(void) {
    threadpool_t *tp = threadpool_init(3);
    int vals[4]={1,-1,2,-2};
    for(int i=0;i<4;i++) threadpool_create_work(tp, &vals[i], increment_counter);
    sleep(2);
    TEST_ASSERT_EQUAL(0, counter);
}

void When_ThreadpoolJobsAddedDynamically_Then_AllExecuted(void) {
    threadpool_t *tp = threadpool_init(2);
    for(int i=0;i<6;i++) { int v=1; threadpool_create_work(tp, &v, increment_counter);}
    sleep(3);
    TEST_ASSERT_EQUAL(6, counter);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(When_ThreadpoolInit_Then_NotNull);
    RUN_TEST(When_ThreadpoolCreateSingleJob_Then_CounterIncremented);
    RUN_TEST(When_ThreadpoolCreateMultipleJobs_Then_CounterIncrementedCorrectly);
    RUN_TEST(When_ThreadpoolMultipleThreads_Then_AllJobsExecuted);
    RUN_TEST(When_ThreadpoolJobWithZeroValue_Then_CounterUnchanged);
    RUN_TEST(When_ThreadpoolSequentialJobs_Then_CounterIncrementedSequentially);
    RUN_TEST(When_ThreadpoolManyJobs_Then_AllExecuted);
    RUN_TEST(When_ThreadpoolSingleThread_Then_AllJobsExecuted);
    RUN_TEST(When_ThreadpoolCreateJobMultipleThreads_Then_AllThreadsWork);
    RUN_TEST(When_ThreadpoolNoJobs_Then_CounterZero);
    RUN_TEST(When_ThreadpoolJobWithNegativeValue_Then_CounterDecremented);
    RUN_TEST(When_ThreadpoolMultipleJobsMixedValues_Then_CounterCorrect);
    RUN_TEST(When_ThreadpoolJobsAddedDynamically_Then_AllExecuted);
    UNITY_END();
}
