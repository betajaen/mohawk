OBJS = main.o mohawk.o
NAME = mohawk

# ============================

CC = m68k-amigaos-gcc
RM = rm
CCFLAGS = -Wall -nostdlib -noixemul -fomit-frame-pointer -fno-tree-loop-distribution -flto -fwhole-program -fno-exceptions
LDFLAGS = -noixemul -fbaserel

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${LDFLAGS} ${INCLUDES} -o $@ ${OBJS}

.cpp.o:
	${CC} ${CFLAGS} ${LDFLAGS} ${INCLUDES} -c $<

.c.o:
	${CC} ${CFLAGS} ${LDFLAGS} ${INCLUDES} -c $<

clean:
	rm -rf *.o ${NAME}