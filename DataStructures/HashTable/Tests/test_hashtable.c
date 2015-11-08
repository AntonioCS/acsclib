#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../HashTable.h"
#include "../../../minunit.h"

int tests_run = 0;
int asserts_run = 0;

static char *test_HashTableInit() {
    HashTable *ht = HashTableInit();

    mu_assert("No hast table", ht != NULL);

    return 0;
}

static char *test_HashTableAdd() {
    HashTable *ht = HashTableInit();

    HashTableAdd(ht, "tes1te", "teste2");

    return 0;
}

mu_all_tests(
        test_HashTableInit,
        test_HashTableAdd
        )

mu_main()