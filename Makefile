CC := gcc
IN := src/*.c
OUT := target/main
CFLAGS := -Wall -pedantic -Wno-deprecated-declarations -ffast-math -fomit-frame-pointer -g3 -lm

all:
	${CC} ${IN} ${CFLAGS} -o ${OUT}

clean:
	rm -f target/*
