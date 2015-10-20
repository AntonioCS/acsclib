CFLAGS=-Wall -g -std=c11
CC=gcc


singleLinkedTest: DataStructures/LinkedList/Single/Test/test.c DataStructures/LinkedList/Single/LinkedList.c DataStructures/LinkedList/Single/LinkedList.h
	$(CC) $(CFLAGS) -o $@ $^

doubleLinkedTest: DataStructures/LinkedList/Double/Tests/test.c DataStructures/LinkedList/Double/DobLinkedList.c DataStructures/LinkedList/Double/DobLinkedList.h
	$(CC) $(CFLAGS) -o $@ $^