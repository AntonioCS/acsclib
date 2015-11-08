CFLAGS=-Wall -g -std=c11
CC=gcc
DOUBLELLFILES=DataStructures/LinkedList/Double/DobLinkedList.c DataStructures/LinkedList/Double/DobLinkedList.h


SingleLinkedTest: DataStructures/LinkedList/Single/Test/test.c DataStructures/LinkedList/Single/LinkedList.c DataStructures/LinkedList/Single/LinkedList.h
	$(CC) $(CFLAGS) -o $@ $^

DoubleLinkedTest: DataStructures/LinkedList/Double/Tests/test.c DataStructures/LinkedList/Double/DobLinkedList.c DataStructures/LinkedList/Double/DobLinkedList.h
	$(CC) $(CFLAGS) -o $@ $^

QueueTest: DataStructures/Queue/Tests/test.c DataStructures/Queue/Queue.c DataStructures/Queue/Queue.h $(DOUBLELLFILES)
	$(CC) $(CFLAGS) -o $@ $^

StackTest: DataStructures/Stack/Tests/test.c DataStructures/Stack/Stack.c DataStructures/Stack/Stack.h $(DOUBLELLFILES)
	$(CC) $(CFLAGS) -o $@ $^

HashTest: DataStructures/HashTable/Tests/test_hash.c
	$(CC) $(CFLAGS) -o $@ $^

HashTableTest: DataStructures/HashTable/Tests/test_hashtable.c DataStructures/HashTable/HashTable.c $(DOUBLELLFILES)
	$(CC) $(CFLAGS) -o $@ $^