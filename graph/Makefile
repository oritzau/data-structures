OBJS=pqueue.o graph.o
CC=cc
CFLAGS=-Wall

pqueue.o: pqueue.c
	$(CC) -c pqueue.c

graph.o: graph.c
	$(CC) -c graph.c

test: $(OBJS) test.c
	cc -o test $(OBJS) test.c 
