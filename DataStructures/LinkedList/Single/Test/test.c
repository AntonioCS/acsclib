#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../LinkedList.h"
#include "../../../../minunit.h"

int tests_run = 0;
int asserts_run = 0;

static char *test_LLInit() {
    LinkedList *ll = LLInit();

    mu_assert("Unable to create Linked List", ll);
    return 0;
}

static char *test_LLAddTail() {
    LinkedList *ll = LLInit();

    char data1[] = "teste";
    char data2[] = "teste";
    char data3[] = "teste";
    char data4[] = "teste";

    LLAddTail(ll, data1);
    LLAddTail(ll, data2);
    LLAddTail(ll, data3);
    LLAddTail(ll, data4);

    mu_assert("Incorrect assignment 1", ll->head->data == data1);
    mu_assert("Incorrect assignment 2", ll->head->next->data == data2);
    mu_assert("Incorrect assignment 3", ll->head->next->next->data == data3);
    mu_assert("Incorrect assignment 4", ll->head->next->next->next->data == data4);

    return 0;
}

static char *test_LLAddHead() {
    LinkedList *ll = LLInit();

    char data1[] = "teste";
    char data2[] = "teste";
    char data3[] = "teste";
    char data4[] = "teste";

    LLAddHead(ll, data1);
    LLAddHead(ll, data2);
    LLAddHead(ll, data3);
    LLAddHead(ll, data4);

    mu_assert("Incorrect assignment 1", ll->head->data == data4);
    mu_assert("Incorrect assignment 2", ll->head->next->data == data3);
    mu_assert("Incorrect assignment 3", ll->head->next->next->data == data2);
    mu_assert("Incorrect assignment 4", ll->head->next->next->next->data == data1);

    return 0;
}

static int compareFuncForLLFindNodeByData(const void *data_given, const void *data_in_node) {
    return strcmp(data_given, data_in_node);
}

static char *test_LLFindNodeByData() {
    LinkedList *ll = LLInit();

    char data1[] = "teste1";
    char data2[] = "teste2";
    char data3[] = "teste3";
    char data4[] = "teste4";

    LLAddHead(ll, data1);
    LLAddHead(ll, data2);
    LLAddHead(ll, data3);
    LLAddHead(ll, data4);

    mu_assert("Unable to find node", LLFindNodeByData(ll, "teste4", compareFuncForLLFindNodeByData) != NULL);

    return 0;
}

static char *test_LLFindNodeByNext() {
    LinkedList *ll = LLInit();

    char data1[] = "teste1";
    char data2[] = "teste2";
    char data3[] = "teste3";
    char data4[] = "teste4";

    LLAddHead(ll, data1);
    LinkedListNode *beforeTail = LLAddHead(ll, data2);
    LLAddHead(ll, data3);
    LLAddHead(ll, data4);

    mu_assert("Does not return correct node", LLFindNodeByNext(ll, ll->tail) == beforeTail);

    return 0;
}

static char *test_LLRemoveNode() {
    LinkedList *ll = LLInit();

    char data1[] = "teste";
    char data2[] = "teste";
    char data3[] = "teste";
    char data4[] = "teste";

    LinkedListNode *tail_to_be_removed = LLAddHead(ll, data1);
    LinkedListNode *tail2_to_be_removed = LLAddHead(ll, data2);
    LLAddHead(ll, data3);
    LinkedListNode *head_to_be_removed = LLAddHead(ll, data4);

    LLRemoveNode(ll, tail_to_be_removed);

    mu_assert("Node tail was not removed", ll->tail != tail_to_be_removed);

    LLRemoveTail(ll);

    mu_assert("Node tail2 was not removed", ll->tail != tail2_to_be_removed);

    LLRemoveHead(ll);

    mu_assert("Node head was not removed", ll->head != head_to_be_removed);

    return 0;
}

mu_all_tests(
        test_LLInit,
        test_LLAddTail,
        test_LLAddHead,

        test_LLFindNodeByData,
        test_LLFindNodeByNext,

        test_LLRemoveNode
        )

mu_main()