# TODO This needs some work still.
CC := gcc
CFLAGS := -Wall -pedantic -Wno-deprecated-declarations -ffast-math -fomit-frame-pointer -g3 -std=c99 -DDEBUG
TARGET := target
SRC := src
SRCS := ${wildcard ${SRC}/*.c}

DEBUG := ${TARGET}/debug
OUT_DIR := ${DEBUG}
OBJ_DIR := ${DEBUG}/obj
OBJ := ${OBJ_DIR}
OBJS := ${patsubst ${SRC}/%.c, ${OBJ}/%.o, ${SRCS}}

LIB := ${OUT_DIR}/hash_table.a

RELEASE := ${TARGET}/release
OUT_DIR_RELEASE := ${RELEASE}
OBJ_DIR_RELEASE := ${RELEASE}/obj
OBJ_RELEASE := ${OBJ_DIR_RELEASE}
OBJS_RELEASE := ${patsubst ${SRC}/%.c, ${OBJ_RELEASE}/%.o, ${SRCS}}

LIB_RELEASE := ${OUT_DIR_RELEASE}/hash_table.a

all: debug

release: OUT_DIR := ${RELEASE}
release: OBJ := ${OBJ_DIR}/release
release: LIB := ${OUT_DIR}/hash_table.a
release: CFLAGS := -Wall -pedantic -Wpadded -Wno-deprecated-declarations -ffast-math -fomit-frame-pointer -O2 -std=c99
release: ${LIB_RELEASE}

${LIB_RELEASE}: ${OBJS_RELEASE}
	mkdir -p ${OUT_DIR}
	ar rcs ${LIB} ${OBJS_RELEASE}

${LIB}: ${OBJS}
	mkdir -p ${OUT_DIR}
	ar rcs ${LIB} ${OBJS}

${OBJ_RELEASE}/%.o: ${SRC}/%.c ${SRC}/%.h
	mkdir -p ${OBJ_RELEASE}
	${CC} -c $< ${CFLAGS} -o $@

${OBJ_RELEASE}/%.o: ${SRC}/%.c
	mkdir -p ${OBJ_RELEASE}
	${CC} -c $< ${CFLAGS} -o $@

${OBJ}/%.o: ${SRC}/%.c ${SRC}/%.h
	mkdir -p ${OBJ}
	${CC} -c $< ${CFLAGS} -o $@

${OBJ}/%.o: ${SRC}/%.c
	mkdir -p ${OBJ}
	${CC} -c $< ${CFLAGS} -o $@

debug: ${LIB}

clean:
	rm -fr ${TARGET} ${OBJ_DIR}/*
