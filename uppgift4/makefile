
CC = gcc
CFLAGS = -O3
LIBS = -lm

HEADERS = calcEChangeAlfa.h 
OBJECTS = calcEChangeAlfa.o H2_uppgift4.o
PROGRAM = H2_uppgift4

%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -f *.o
	touch *.c

