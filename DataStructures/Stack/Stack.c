
#include "Stack.h"

Stack *StackInit() {
    return DobLLInit();
}

void StackPush(Stack *s, void *data) {
    DobLLAddHead(s, data);
}

void *StackPop(Stack *s) {
    return DobLLRemoveHead(s);
}
