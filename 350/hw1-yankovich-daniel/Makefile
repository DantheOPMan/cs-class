OBJS = reality.o reality4.o
CC = gcc
CFLAGS = -fno-stack-protector
PROGS = reality reality4

all:	$(PROGS)

reality:    reality.o
	$(CC) $(CFLAGS) reality.c -o reality
reality4:    reality4.o
	$(CC) $(CFLAGS) reality4.c -o reality4
clean:
	rm *.o *~ reality reality4