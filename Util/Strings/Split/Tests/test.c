/*
 * File:   main.c
 * Author: antoniocs
 *
 * Created on 12 de Dezembro de 2015, 12:19
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../split.h"
#include "../../../../minunit.h"

int tests_run = 0;
int asserts_run = 0;

static char *test_split() {

    char *test_string = "Test1 Test2 Test3 Test4";
    struct splitString *test = split(test_string, " ");

    mu_assert("Incorrect total", test->total == 4);

    mu_assert("Wrong value for 0", strcmp("Test1", test->tokens[0]) == 0);
    mu_assert("Wrong value for 1", strcmp("Test2", test->tokens[1]) == 0);
    mu_assert("Wrong value for 2", strcmp("Test3", test->tokens[2]) == 0);
    mu_assert("Wrong value for 3", strcmp("Test4", test->tokens[3]) == 0);

    return 0;
}

mu_all_tests(
        test_split
        )

mu_main()