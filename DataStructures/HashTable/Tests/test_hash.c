#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../HashTable.c"
#include "../../../minunit.h"

int tests_run = 0;
int asserts_run = 0;

#define HASH_SIZE 8

char samples_keys[][25] = {
    "Fermina Norwood",
    "Lorena Oliver",
    "Edmund Negus",
    "Evelyn Lev",
    "Cherelle Freyer",
    "Norine Fiore",
    "Lasonya Shurtliff",
    "Hien Vineyard",
    "Lily Raffa",
    "Janella Carls",
    "Jina Graybill",
    "Nathaniel Gardener",
    "Juli Poon",
    "Florene Bastien",
    "Ahmed Speicher",
    "Jerri Aucoin",
    "Jerry Nickerson",
    "Shawna Melecio",
    "Abe Leard",
    "Eden Boulton",
    "Genesis Smitherman",
    "Ashton Pears",
    "Dona Dyches",
    "Adele Patman",
    "Vincenza Nunes",
    "Arlyne Krok",
    "Jarod Shay",
    "Moon Whitcher",
    "Zofia Boger",
    "Maryetta Batdorf",
    "Kory Sykora",
    "Cheryle Sandman",
    "Luvenia Rebuck",
    "Tiesha Brunswick",
    "Huong Milliken",
    "Viviana Doverspike",
    "Chasidy Plumlee",
    "Alia Perrier",
    "Isa Angles",
    "Shaunte Palomba",
    "Tammera Mcentee",
    "Nona Pappan",
    "Tamela Romero",
    "Regena Eller",
    "Leticia Arends",
    "Alta Spore",
    "Tessa Yamamoto",
    "Izetta Mclarty",
    "Wilson Espino",
    "Gabrielle Meche",
    "benicia",
    "smoulder",
    "playas",
    "unscoured",
    "fancywork",
    "tragicomedy",
    "necessaries",
    "leftwardly",
    "nonreputable",
    "wenonah",
    "silversmithing",
    "unrenunciative",
    "remontoir",
    "franchise",
    "understuff",
    "cheeringly",
    "retelegraph",
    "waterbury",
    "jamnagar",
    "nonclimactic",
    "senior",
    "epimer",
    "scantly",
    "camailed",
    "overpollinating",
    "undoing",
    "ballonnï¿¥ï¾½",
    "bo''s''n",
    "extrasystole",
    "nonsolvent",
    "nonspeaker",
    "alcoholism",
    "centuplication",
    "undemolished",
    "deoxygenise",
    "kilowatt",
    "theonomy",
    "jacalin",
    "overobsequious",
    "dysergia",
    "leucothea",
    "headlock",
    "striker",
    "periodically",
    "bedrock",
    "vaudevillian",
    "firebird",
    "bombasine",
    "unfrigid",
    "uncravatted"
};

static char *test_hash() {

    //pretend hash table
    int hash_table[HASH_SIZE] = {0};

    unsigned t, t2;

    unsigned int size = (sizeof samples_keys / sizeof samples_keys[0]);
    unsigned int hash_key;

    for (int i = 0; i < size; i++) {
        t = hash(samples_keys[i], strlen(samples_keys[i])) & 0x08;
        t2 = hash(samples_keys[i], strlen(samples_keys[i])) % 8;

        if (t != t2) {
            printf("Hashs not equal\n");

            printf("TESTE: %u\n", t);
            printf("TESTE: %u\n", t2);
        }
        else {
            printf("Equal: %u\n", t);
        }
        //printf("TESTE: %u\n", );
        //printf("TESTE: %u\n", );
        hash_key = hash(samples_keys[i], strlen(samples_keys[i])) % HASH_SIZE;
        hash_table[hash_key] += 1;
        //printf("%s - %u\n", keys[i], keys_numbers[i]);
    }

    int key_count[10] = {0};
    for (int i = 0; i < HASH_SIZE; i++) {
        if (hash_table[i] >= 10) {
            printf("Bigger than 10\n");
        } else {
            key_count[hash_table[i]] += 1;
        }
        //printf("key %d - %d\n", i, hash_table[i]);
    }

    for (int i = 0; i < 10; i++) {
        printf("key %d - %d\n", i, key_count[i]);
    }


    return 0;
}

mu_all_tests(
        test_hash
        )

mu_main()