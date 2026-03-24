CC=gcc
CFLAGS=-Iinclude
TARGET=build/main
SRCS=$(wildcard src/*.c)
OBJS=$(patsubst src/%.c, build/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ -o $@

build/%.o: src/%.c
	@mkdir -p build/
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf build/
