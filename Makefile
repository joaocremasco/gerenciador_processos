CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -O2
OBJS = main.o heap.o processo.o tempo.o

all: gerente

gerente: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

main.o: main.c heap.h processo.h tempo.h
	$(CC) $(CFLAGS) -c main.c

heap.o: heap.c heap.h processo.h tempo.h
	$(CC) $(CFLAGS) -c heap.c

processo.o: processo.c processo.h tempo.h
	$(CC) $(CFLAGS) -c processo.c

tempo.o: tempo.c tempo.h
	$(CC) $(CFLAGS) -c tempo.c

run: gerente
	@./gerente

clean:
	rm -f $(OBJS) gerente

.PHONY: all run clean