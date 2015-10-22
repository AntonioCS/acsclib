#include <stdio.h>
#include <stdlib.h>
#include "../Stack.h"
#include "../../../minunit.h"

int tests_run = 0;
int asserts_run = 0;

static char *test_StackInit() {
    Stack *s = StackInit();

    mu_assert("Unable to create Stack", s);
    return 0;
}

static char *test_PushPop() {
    Stack *s = StackInit();

    char data1[] = "test 1";
    char data2[] = "test 2";
    char data3[] = "test 3";
    char data4[] = "test 4";

    StackPush(s, data1);
    StackPush(s, data2);
    StackPush(s, data3);
    StackPush(s, data4);
    
    mu_assert("Incorrect data 1", StackPop(s) == data4);
    mu_assert("Incorrect data 2", StackPop(s) == data3);
    mu_assert("Incorrect data 3", StackPop(s) == data2);
    mu_assert("Incorrect data 4", StackPop(s) == data1);

    return 0;
}

mu_all_tests(
        test_StackInit,
        test_PushPop
        )

mu_main()
