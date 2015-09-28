CFLAGS=-Wall -g -std=c11
CC=gcc


singleLinkedTest: DataStructures/LinkedList/Single/Test/test.c DataStructures/LinkedList/Single/LinkedList.c DataStructures/LinkedList/Single/LinkedList.h
	$(CC) $(CFLAGS) -o $@ $^