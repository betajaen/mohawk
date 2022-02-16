OBJS = main.o game.o
NAME = mohawk

# ============================

CXX = m68k-amigaos-gcc
RM = rm
CP = cp
CXXFLAGS = -noixemul -fno-exceptions -fno-rtti
LDFLAGS = -noixemul -fno-exceptions -Os

all: ${NAME}

${NAME}: ${OBJS}
	${CXX} ${CFLAGS} ${LDFLAGS} ${INCLUDES} -o $@ ${OBJS}
	${CP} ${NAME} ../progdir/${NAME}
	${CP} ${NAME}.info ../progdir/${NAME}.info

.cpp.o:
	${CXX} ${CFLAGS} ${LDFLAGS} ${INCLUDES} -c $<

.c.o:
	${CXX} ${CFLAGS} ${LDFLAGS} ${INCLUDES} -c $<

clean:
	rm -rf *.o ${NAME}