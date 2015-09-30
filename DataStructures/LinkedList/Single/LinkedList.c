
#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "../../../dbg.h"

enum LLAddStrategy {
    HEAD,
    TAIL
};

static LinkedListNode *NodeInit();
static int LLAddBase(LinkedList *, void *, enum LLAddStrategy);
static void *LLRemoveBase(LinkedList *, LinkedListNode *);

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

/**
 * Add an item to the linked list in the head or the tail
 * 
 * @param ll
 * @param data
 * @param type
 * @return int (will be 1 for failure and 0 for sucess)
 */
int LLAddBase(LinkedList *ll, void *data, enum LLAddStrategy type) {
    check(ll, "LLAddBase received null pointer");
    LinkedListNode *node = NodeInit(data, NULL);

    if (ll->head == NULL) {
        ll->current = ll->tail = ll->head = node;
    } else {
        if (type == HEAD) {
            node->next = ll->head;
            ll->current = ll->head = node;
        } else {
            ll->current = ll->tail->next = node;
            ll->tail = ll->tail->next;
        }
    }

    return 0;
error:
    return 1;
}

/**
 * Add a node to the start of the Linked List
 * 
 * @param ll
 * @param data
 * @return
 */
int LLAddHead(LinkedList *ll, void *data) {
    return LLAddBase(ll, data, HEAD);
}

/**
 * Add a node to the end of the Linked List
 *
 * @param ll
 * @param data
 * @return
 */
int LLAddTail(LinkedList *ll, void *data) {
    return LLAddBase(ll, data, TAIL);
}

/**
 * Shorter alias for LLAddTail
 * 
 * @param ll
 * @param data
 * @return
 */
int LLAdd(LinkedList *ll, void *data) {
    return LLAddTail(ll, data);
}

LinkedListNode *NodeInit(void *data, LinkedListNode *next) {
    LinkedListNode *lln = malloc(sizeof (LinkedListNode));
    check(lln, "Unable to allocate memory for linked list node");

    lln->data = data;
    lln->next = next;

    return lln;
error:
    return NULL;
}

void *LLRemoveHead(LinkedList *ll) {
    return LLRemoveNode(ll, ll->head);
}

void *LLRemoveTail(LinkedList *ll) {
    return LLRemoveNode(ll, ll->tail);
}

void *LLRemoveNode(LinkedList *ll, LinkedListNode *node) {

}