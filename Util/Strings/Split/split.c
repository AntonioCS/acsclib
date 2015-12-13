#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "split.h"

#define DEFAULT_TOKEN_SIZE 10

static struct splitString* initSplitString() {
    struct splitString *s = malloc(sizeof (struct splitString));

    if (s) {
        s->total = 0;
        s->size = DEFAULT_TOKEN_SIZE;
        s->tokens = malloc(sizeof (char *) * DEFAULT_TOKEN_SIZE);

        for (int i = 0; i < DEFAULT_TOKEN_SIZE; i++) {
            s->tokens[i] = NULL;
        }


        return s;
    }

    return NULL;
}

/**
 * Adjust the size of the tokens variable if necessary
 * @param s
 */
static void adjustSize(struct splitString *s) {
    if (s->total == s->size) {
        s->size += DEFAULT_TOKEN_SIZE;

        char **temp_tokens = realloc(s->tokens, sizeof (char *) * s->size);

        if (temp_tokens) {
            s->tokens = temp_tokens;
        }
    }
}

struct splitString* split(const char *string, const char *delimiter) {
    unsigned size = strlen(string) + 1;
    char tmp[size];
    char *token = NULL;
    struct splitString *s = initSplitString();

    if (s == NULL) {
        goto error;
    }

    memcpy(tmp, string, size);

    token = strtok(tmp, delimiter);

    while (token != NULL) {
        int bsize = strlen(token) + 1;

        s->tokens[s->total] = malloc(bsize);

        if (s->tokens[s->total]) {
            memcpy(s->tokens[s->total], token, bsize);
        }
        else {
            splitFree(&s);
            goto error;
        }

        s->total++;

        adjustSize(s);
        token = strtok(NULL, delimiter);
    }

    return s;

error:

    return NULL;
}

/**
 * Clear all token and the splitString
 * @param s
 */
void splitFree(struct splitString **s) {
    for (int i = 0; i < (*s)->total; i++) {
        free((*s)->tokens[i]);
        (*s)->tokens[i] = NULL;
    }

    free((*s)->tokens);
    (*s)->tokens = NULL;

    free(*s);
    *s = NULL;
}