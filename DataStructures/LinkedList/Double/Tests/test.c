#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../DobLinkedList.h"
#include "../../../../minunit.h"

int tests_run = 0;
int asserts_run = 0;

static bool comp(const void *data_given, const void *data_in_node) {
    return (strcmp(data_given, data_in_node) == 0);
}

static char *test_DobLLInit() {
    DobLinkedList *dobll = DobLLInit();

    mu_assert("Unable to create Linked List", dobll);
    return 0;
}

static char *test_DobLLAddHead() {
    DobLinkedList *dobll = DobLLInit();

    char data1[] = "test 1";
    char data2[] = "test 2";
    char data3[] = "test 3";
    char data4[] = "test 4";

    DobLLAddHead(dobll, data1);
    DobLLAddHead(dobll, data2);
    DobLLAddHead(dobll, data3);
    DobLLAddHead(dobll, data4);

    mu_assert("Incorrect assignment 1.1", dobll->head->data == data4);
    mu_assert("Incorrect assignment 1.2", dobll->head->prev == NULL);

    mu_assert("Incorrect assignment 2.1", dobll->head->next->data == data3);
    mu_assert("Incorrect assignment 2.2", dobll->head->next->prev->data == data4);

    mu_assert("Incorrect assignment 3.1", dobll->head->next->next->data == data2);
    mu_assert("Incorrect assignment 3.2", dobll->head->next->next->prev->data == data3);

    mu_assert("Incorrect assignment 4.1", dobll->head->next->next->next->data == data1);
    mu_assert("Incorrect assignment 4.2", dobll->head->next->next->next->prev->data == data2);
    mu_assert("Incorrect assignment 4.3", dobll->head->next->next->next->next == NULL);

    return 0;
}

static char *test_DobLLAddTail() {
    DobLinkedList *dobll = DobLLInit();

    char data1[] = "test 1";
    char data2[] = "test 2";
    char data3[] = "test 3";
    char data4[] = "test 4";

    DobLLAddTail(dobll, data1);
    DobLLAddTail(dobll, data2);
    DobLLAddTail(dobll, data3);
    DobLLAddTail(dobll, data4);

    mu_assert("Incorrect assignment 1.1", dobll->head->data == data1);
    mu_assert("Incorrect assignment 1.2", dobll->head->prev == NULL);

    mu_assert("Incorrect assignment 2.1", dobll->head->next->data == data2);
    mu_assert("Incorrect assignment 2.2", dobll->head->next->prev->data == data1);

    mu_assert("Incorrect assignment 3.1", dobll->head->next->next->data == data3);
    mu_assert("Incorrect assignment 3.2", dobll->head->next->next->prev->data == data2);

    mu_assert("Incorrect assignment 4.1", dobll->head->next->next->next->data == data4);
    mu_assert("Incorrect assignment 4.2", dobll->head->next->next->next->prev->data == data3);
    mu_assert("Incorrect assignment 4.3", dobll->head->next->next->next->next == NULL);

    return 0;
}

static char *test_DobLLRemoveTail() {
    DobLinkedList *dobll = DobLLInit();

    char data1[] = "test 1";
    char data2[] = "test 2";
    char data3[] = "test 3";
    char data4[] = "test 4";

    DobLinkedListNode *tail_to_be_removed = DobLLAddHead(dobll, data1);
    
    DobLLAddHead(dobll, data2);
    DobLLAddHead(dobll, data3);
    DobLLAddHead(dobll, data4);

    DobLLRemoveTail(dobll);
    
    mu_assert("Node tail was not removed", dobll->tail != tail_to_be_removed);

    return 0;
}

static char *test_DobLLRemoveHead() {
    DobLinkedList *dobll = DobLLInit();

    char data1[] = "test 1";
    char data2[] = "test 2";
    char data3[] = "test 3";
    char data4[] = "test 4";

    DobLLAddHead(dobll, data1);
    DobLLAddHead(dobll, data2);
    DobLLAddHead(dobll, data3);
    DobLinkedListNode *head_to_be_removed = DobLLAddHead(dobll, data4);

    DobLLRemoveHead(dobll);
    
    mu_assert("Node tail was not removed", dobll->head != head_to_be_removed);

    return 0;
}

static char *test_DobLLRemoveHeadWhichIsAlsoTail() {
    DobLinkedList *dobll = DobLLInit();

    char data1[] = "test 1";

    DobLLAddHead(dobll, data1);

    DobLLRemoveHead(dobll);

    mu_assert("Node head and tail were not set to null", dobll->head == NULL && dobll->tail == NULL);

    return 0;
}

static char *test_DobLLRemoveTailWhichIsAlsoHead() {
    DobLinkedList *dobll = DobLLInit();

    char data1[] = "test 1";

    DobLLAddHead(dobll, data1);

    DobLLRemoveTail(dobll);

    mu_assert("Node tail and head were not set to null", dobll->head == NULL && dobll->tail == NULL);

    return 0;
}

static char *test_DobLLRemoveOnEmptyList() {
    DobLinkedList *dobll = DobLLInit();

    mu_assert("Node tail and head were not set to null", DobLLRemoveTail(dobll) == NULL);

    return 0;
}


static char *test_DobLLFindNodeByData() {
    DobLinkedList *dobll = DobLLInit();

    char data1[] = "test 1";
    char data2[] = "test 2";
    char data3[] = "test 3";
    char data4[] = "test 4";

    DobLLAddHead(dobll, data1);
    DobLLAddHead(dobll, data2);
    DobLinkedListNode *item_to_be_found = DobLLAddHead(dobll, data3);
    DobLLAddHead(dobll, data4);

    DobLinkedListNode *found_node = DobLLFindNodeByData(dobll, "test 3", comp);

    mu_assert("Node tail was not removed", found_node == item_to_be_found);

    return 0;
}

static char *test_DobLLNodesCount() {
    DobLinkedList *dobll = DobLLInit();

    char data[][8] = {
        "test 1",
        "test 1",
        "test 1",
        "test 1",
        "test 1",
        "test 1",
        "test 1",
        "test 1",
        "test 1",
        "test 1",
        "test 1",
        "test 1",
        "test 1",
        "test 1",
        "test 1",
        "test 1",
        "test 1",
        "test 1",
        "test 1"
    };

    int array_size = (sizeof(data)/sizeof(data[0]));
    for (int i = 0; i < array_size; i++) {
        DobLLAddHead(dobll, data[i]);
    }

    mu_assert("Node tail was not removed", dobll->nodeCount == array_size);

    DobLLRemoveHead(dobll);
    DobLLRemoveHead(dobll);
    DobLLRemoveHead(dobll);

    mu_assert("Node tail was not removed", dobll->nodeCount == (array_size - 3));

    return 0;
}

mu_all_tests(
        test_DobLLInit,
        
        test_DobLLAddHead,
        test_DobLLAddTail,
        
        test_DobLLRemoveTail,
        test_DobLLRemoveHead,

        test_DobLLRemoveHeadWhichIsAlsoTail,
        test_DobLLRemoveTailWhichIsAlsoHead,
        test_DobLLRemoveOnEmptyList,

        test_DobLLFindNodeByData,

        test_DobLLNodesCount
        )

mu_main()