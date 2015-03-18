CC=gcc
CFLAGS=-c -Wall -Werror -std=c89 -pedantic
LDFLAGS=
SOURCES=$(shell find src/ -type f -name '*.c')
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=tl
all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE)
	@find src/ -type f -name '*.o' -exec rm -vf {} \;

.PHONY: clean
