CC=gcc
LINK=gcc
TARGET=CharTest.exe
OBJS=CharTest.o character.o file.o inventory.o
LIBS=
CFLAGS= -g -Wall -Wextra

all: ${TARGET}

${TARGET}: ${OBJS}
	${CC} -o ${TARGET} ${OBJS} ${LIBS}

.PHONY : clean

clean:
	del -f ${TARGET} core*
	del -f *.o core*