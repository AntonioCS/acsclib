#include <stdio.h>
#include <stdlib.h>
#include "../Queue.h"
#include "../../../minunit.h"

int tests_run = 0;
int asserts_run = 0;

static char *test_QueueInit() {
    Queue *q = QueueInit();

    mu_assert("Unable to create Linked List", q);
    return 0;
}

static char *test_EnqueueDequeue() {

    Queue *q = QueueInit();

    char data1[] = "test 1";
    char data2[] = "test 2";
    char data3[] = "test 3";
    char data4[] = "test 4";

    QueueEnQueue(q, data1);
    QueueEnQueue(q, data2);
    QueueEnQueue(q, data3);
    QueueEnQueue(q, data4);

    mu_assert("Incorrect data 1", QueueDeQueue(q) == data1);
    mu_assert("Incorrect data 2", QueueDeQueue(q) == data2);
    mu_assert("Incorrect data 3", QueueDeQueue(q) == data3);
    mu_assert("Incorrect data 4", QueueDeQueue(q) == data4);

    return 0;
}

mu_all_tests(
        test_QueueInit,
        test_EnqueueDequeue
        )

mu_main()
