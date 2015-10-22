/* 
 * File:   Stack.h
 * Author: antoniocs
 *
 * Created on 21 de Outubro de 2015, 11:32
 */

#include "../LinkedList/Double/DobLinkedList.h"

#ifndef STACK_H
#define	STACK_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef DobLinkedList Stack;

    Stack *StackInit();
    void StackPush(Stack *, void *);
    void *StackPop(Stack *);

#ifdef	__cplusplus
}
#endif

#endif	/* STACK_H */

