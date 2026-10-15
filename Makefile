CC     = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -O2
OBJS   = main.o heap.o processo.o tempo.o

gerente: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

main.o: main.c heap.h processo.h tempo.h
heap.o: heap.c heap.h processo.h tempo.h
processo.o: processo.c processo.h tempo.h
tempo.o: tempo.c tempo.h

clean:
	rm -f $(OBJS) gerente

.PHONY: clean