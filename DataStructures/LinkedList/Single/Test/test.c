#include <stdio.h>
#include <stdlib.h>
#include "../LinkedList.h"
#include "../../../../minunit.h"

int tests_run = 0;
int asserts_run = 0;
static LinkedList *ll;

static char *test_LLInit() {
    ll = LLInit();

    mu_assert("Unable to create Linked List", ll);
    return 0;
}

static char *test_LLAddBase() {    
    char data1[] = "teste";
    char data2[] = "teste";
    char data3[] = "teste";
    char data4[] = "teste";

    LLAddBase(ll, data1);
    LLAddBase(ll, data2);
    LLAddBase(ll, data3);
    LLAddBase(ll, data4);

    return 0;
}


mu_all_tests(
        test_LLInit,
        test_LLAddBase
)

mu_main()