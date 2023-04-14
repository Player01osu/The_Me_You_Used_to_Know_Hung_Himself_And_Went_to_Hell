CC := gcc
IN := src/*.c
OUT := target/main
CFLAGS := -Wall -pedantic -Wno-deprecated-declarations -ffast-math -fomit-frame-pointer -g3 -std=c99
DEBUG_FLAGS := -DDEBUG

all:
	${CC} ${IN} ${CFLAGS} -o ${OUT}

debug:
	${CC} ${IN} ${CFLAGS} ${DEBUG_FLAGS} -o ${OUT}

clean:
	rm -f target/*
