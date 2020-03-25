override CFLAGS+=-std=c11 -xc -Wall -Wextra `pkg-config --cflags readline` -Iconcerns
override LDFLAGS+=`pkg-config --libs readline`

ifneq ($(RELEASE),1)
    override CFLAGS+=-fsanitize=address -ggdb -DDEBUG
    override LDFLAGS+=-fsanitize=address -ggdb
endif

default: all
all: simplesh tests

SRCS=$(wildcard */*/*.c)
OBJS=$(SRCS:.c=.o)

simplesh: simplesh.o ${OBJS}
	$(CC) $< ${OBJS} ${LDFLAGS} -o $@

tests: tests.o ${OBJS}
	$(CC) $< ${OBJS} ${LDFLAGS} -o $@

%.o: %.c
	$(CC) ${CFLAGS} -c -MMD $< -o $@

.PHONY: default all fmt clean tests
test: tests
	ASAN_OPTIONS=detect_leaks=0 ./tests
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
