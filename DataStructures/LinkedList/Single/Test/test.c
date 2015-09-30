#include <stdio.h>
#include <stdlib.h>
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


mu_all_tests(
        test_LLInit,
        test_LLAddTail,
        test_LLAddHead
)

mu_main()