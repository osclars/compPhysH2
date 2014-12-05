
CC = gcc
CFLAGS = -O3
LIBS = -lm

HEADERS = calcEKeepAlfa.h 
OBJECTS = calcEKeepAlfa.o H2_uppgift3.o
PROGRAM = H2_uppgift3

%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -f *.o
	touch *.c

