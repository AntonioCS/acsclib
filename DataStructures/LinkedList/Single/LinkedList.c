
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "LinkedList.h"
#include "../../../dbg.h"

typedef int (*LLFindCompareFuncPtr)(const void *, const void *);

enum LLAddStrategy {
    HEAD,
    TAIL
};

struct LLFindNodeBaseParams {
    LinkedList *ll;

    void *data;
    LLFindCompareFuncPtr compareFunc;

    LinkedListNode *node;
    LinkedListNode *next;
};

struct FindResult {
    LinkedListNode *prev;
    LinkedListNode *node;
};

typedef bool(*findByFuncPtr)(struct LLFindNodeBaseParams *, struct FindResult *, LinkedListNode *);

//<editor-fold defaultstate="collapsed" desc="Private functions">


static bool FindResultSetResult(bool condition, struct FindResult *res, LinkedListNode *node) {
    if (condition) {
        res->node = node;
    } else {
        res->prev = node;
    }

    return condition;
}

static bool FindByData(struct LLFindNodeBaseParams *params, struct FindResult *res, LinkedListNode *node) {
    return FindResultSetResult(params->compareFunc(params->data, node->data) == 0, res, node);
}

static bool FindByNode(struct LLFindNodeBaseParams *params, struct FindResult *res, LinkedListNode *node) {
    return FindResultSetResult(params->node == node, res, node);
}

static bool FindByNextNode(struct LLFindNodeBaseParams *params, struct FindResult *res, LinkedListNode *node) {
    return FindResultSetResult(params->next == node->next, res, node);
}

struct FindResult *InitFindResult() {
    struct FindResult *res = malloc(sizeof (struct FindResult));
    check(res, "Unable to allocate memory for FindResult");

    res->node = NULL;
    res->prev = NULL;

    return res;

error:
    return NULL;
}

static struct FindResult *FindNodeBase(struct LLFindNodeBaseParams *params) {
    findByFuncPtr fptr = NULL;

    if (params->data != NULL && params->compareFunc != NULL) {
        fptr = FindByData;
    } else if (params->node != NULL) {
        fptr = FindByNode;
    } else if (params->next != NULL) {
        fptr = FindByNextNode;
    }

    check(fptr, "Bad params for FindNodeBase, can't determine find function");

    LinkedListNode *node = params->ll->head;
    struct FindResult *res = InitFindResult();

    check(res, "Unable to allocate memory for FindResult structure");
    bool foundNode = false;

    while (node != NULL) {
        if ((foundNode = fptr(params, res, node))) {
            break;
        }
        node = node->next;
    }

    if (foundNode == false) {
        res->node = NULL;
        res->prev = NULL;
    }

    return res;

error:
    return NULL;
}

static struct FindResult *LLFindNode(LinkedList *ll, LinkedListNode *node) {

    struct LLFindNodeBaseParams fnbParams = {
        .ll = ll,
        .node = node
    };
    struct FindResult *res = FindNodeBase(&fnbParams);
    return res;
}


/**
 *
 * @param data
 * @param next
 * @return
 */
static LinkedListNode *NodeInit(void *data, LinkedListNode *next) {
    LinkedListNode *lln = malloc(sizeof (LinkedListNode));
    check(lln, "Unable to allocate memory for linked list node");

    lln->data = data;
    lln->next = next;

    return lln;
error:
    return NULL;
}

/**
 * Add an item to the linked list in the head or the tail
 *
 * @param ll
 * @param data
 * @param type
 * @return LinkedListNode *
 */
static LinkedListNode *LLAddBase(LinkedList *ll, void *data, enum LLAddStrategy stype) {
    check(ll, "LLAddBase received null pointer");
    LinkedListNode *node = NodeInit(data, NULL);

    if (ll->head == NULL) {
        ll->tail = ll->head = node;
    } else {
        if (stype == HEAD) {
            node->next = ll->head;
            ll->head = node;
        } else {
            ll->tail->next = node;
            ll->tail = ll->tail->next;
        }
    }

    return node;
error:
    return NULL;
}

//</editor-fold>

/**
 * Initialize a linked list
 * 
 * @return LinkedList *
 */
LinkedList *LLInit() {
    LinkedList *ll = malloc(sizeof (LinkedList));
    check(ll, "Unable to allocate memory for linked list");

    ll->head = NULL;
    ll->tail = NULL;

    return ll;

error:
    return NULL;
}

//<editor-fold defaultstate="collapsed" desc="Add Functions">

/**
 * Add a node to the start of the Linked List
 * 
 * @param ll
 * @param data
 * @return LinkedListNode *
 */
LinkedListNode *LLAddHead(LinkedList *ll, void *data) {
    return LLAddBase(ll, data, HEAD);
}

/**
 * Add a node to the end of the Linked List
 *
 * @param ll
 * @param data
 * @return LinkedListNode *
 */
LinkedListNode *LLAddTail(LinkedList *ll, void *data) {
    return LLAddBase(ll, data, TAIL);
}

/**
 * Shorter alias for LLAddTail
 * 
 * @param ll
 * @param data
 * @return LinkedListNode *
 */
LinkedListNode *LLAdd(LinkedList *ll, void *data) {
    return LLAddTail(ll, data);
}

//</editor-fold>

//<editor-fold defaultstate="collapsed" desc="Remove functions">

/**
 * @param ll Pointer to linkedlist
 * @return void * to the data in the node
 */
void *LLRemoveHead(LinkedList *ll) {
    return LLRemoveNode(ll, ll->head);
}

/**
 * @param ll Pointer to linkedlist
 * @return void * to the data in the node
 */
void *LLRemoveTail(LinkedList *ll) {
    return LLRemoveNode(ll, ll->tail);
}

/**
 *
 * @param ll Pointer to linkedlist
 * @param node Pointer to node to delete
 * @return void * to the data in the node
 */
void *LLRemoveNode(LinkedList *ll, LinkedListNode *node) {
    void *data = node->data;
    struct FindResult *res = LLFindNode(ll, node);

    check(res->node, "Node not found on List");

    if (node == ll->head) {
        ll->head = ll->head->next;

        if (ll->head == NULL) {
            ll->tail = NULL;
        }
    } else {
        res->prev->next = node->next;

        if (node == ll->tail) {
            ll->tail = res->prev;
        }
    }

    free(node);
    return data;

error:
    return NULL;
}
//</editor-fold>

//<editor-fold defaultstate="collapsed" desc="Find functions">

/** 
 * @param ll
 * @param data
 * @param func
 * @return
 */
LinkedListNode *LLFindNodeByData(LinkedList *ll, void *data, int (*func)(const void *, const void *)) {

    struct LLFindNodeBaseParams fnbParams = {
        .ll = ll,
        .data = data,
        .compareFunc = func
    };
    struct FindResult *res = FindNodeBase(&fnbParams);

    LinkedListNode *node = res->node;
    free(res);

    return node;
}

/**
 * @param ll
 * @param nodeNext
 * @return
 */
LinkedListNode *LLFindNodeByNext(LinkedList *ll, LinkedListNode *nodeNext) {

    struct LLFindNodeBaseParams fnbParams = {
        .ll = ll,
        .next = nodeNext
    };
    struct FindResult *res = FindNodeBase(&fnbParams);

    LinkedListNode *node = res->node;
    free(res);

    return node;
}

//</editor-fold>