
#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "../../../dbg.h"

static LinkedListNode *NodeInit();

LinkedList *LLInit() {
    LinkedList *ll = malloc(sizeof (LinkedList));
    check(ll, "Unable to allocate memory for linked list");

    ll->current = NULL;
    ll->head = NULL;
    ll->tail = NULL;

    return ll;

error:
    return NULL;
}

int LLAddBase(LinkedList *ll, void *data) {
    check(ll, "LLAddBase received null pointer");
    LinkedListNode *node = NodeInit(data, NULL);

    if (ll->head == NULL) {
        ll->current = ll->tail = ll->head = node;
    } else {
        ll->current = ll->tail->next = node;
        ll->tail = ll->tail->next;
    }

    return 1;    
error:
    return 0;
}

static LinkedListNode *NodeInit(void *data, LinkedListNode *next) {
    LinkedListNode *lln = malloc(sizeof (LinkedListNode));
    check(lln, "Unable to allocate memory for linked list node");

    lln->data = data;
    lln->next = next;

    return lln;
error:
    return NULL;
}