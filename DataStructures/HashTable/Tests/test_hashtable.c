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

static char *test_HashTableAdd_HashTableGet() {
    HashTable *ht = HashTableInit();

    mu_assert("Failed to set the value", (HashTableAdd(ht, "test", "test2")));

    mu_assert("Failed to retrieve the value", strcmp(HashTableGet(ht, "test"), "test2") == 0);

    return 0;
}

static char *test_HashTableAddOverwrite() {
    HashTable *ht = HashTableInit();

    mu_assert("Failed to set the value", (HashTableAdd(ht, "test", "test2")));
    mu_assert("Failed to retrieve the value", strcmp(HashTableGet(ht, "test"), "test2") == 0);

    //HashTable_Debug(ht);

    mu_assert("Failed to re set the value", (HashTableAdd(ht, "test", "test2234")));
    mu_assert("Failed to retrieve altered the value", strcmp(HashTableGet(ht, "test"), "test2234") == 0);

    HashTable_Debug(ht);

    return 0;
}

static char *test_HashTableAddForceRealloc() {

    char testewords[] = {
        "winter", "wren",
        "ambiguous", "mere",
        "honorable", "hysterical",
        "dust", "divide",
        "rifle", "notice",
        "risk", "handsomely",
        "well-to-do", "hall",
        "sedate", "wrong",
        "bow", "exotic",
        "confused", "furry",
        "decision", "alive",
        "knife", "silver",
        "kitty", "recondite",
        "face", "identify",
        "bushes", "rainy",
        "normal", "immense",
        "sky", "borrow",
        "soft", "twig",
        "sweet", "scarecrow",
        "unkempt", "toothsome",
        "sneaky", "desk",
        "relax", "can",
        "tall", "gold",
        "sail", "raspy",
        "squeamish", "maid",
        "grass", "grubby",
        "ignorant", "expect",
        "touch", "ambitious",
        "fancy", "men",
        "slave", "glue",
        "faded", "pan",
        "babies", "haunt",
        "border", "settle"
    };

    


    return 0;
}



mu_all_tests(
        test_HashTableInit,
        test_HashTableAdd_HashTableGet,
        test_HashTableAddOverwrite
        )

mu_main()