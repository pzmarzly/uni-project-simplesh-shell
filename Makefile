override CFLAGS+=-std=c11 -xc -Wall -Wextra `pkg-config --cflags readline` -Iconcerns
override LDFLAGS+=`pkg-config --libs readline`

default: all
all: simplesh

SRCS=$(wildcard *.c) $(wildcard */*/*.c)
OBJS=$(SRCS:.c=.o)

simplesh: ${OBJS}
	$(CC) ${OBJS} ${LDFLAGS} -o simplesh

%.o: %.c
	$(CC) ${CFLAGS} -c -MMD $< -o $@

.PHONY: default all fmt clean
fmt:
	-clang-format -i *.c || true
	-clang-format -i *.h || true
	-clang-format -i */*.c || true
	-clang-format -i */*.h || true
	-clang-format -i */*/*.c || true
	-clang-format -i */*/*.h || true
clean:
	-rm -f simplesh || true
	-rm -f *.o || true
	-rm -f *.d || true
	-rm -f */*.o || true
	-rm -f */*.d || true
	-rm -f */*/*.o || true
	-rm -f */*/*.d || true

-include *.d
