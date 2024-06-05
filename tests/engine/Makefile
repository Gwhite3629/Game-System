CC=gcc
LINK=gcc

ENGINE=engine

ENGINEOBS=engine.o

LIBS=-lm -lpthread
CFLAGS=-fPIC -D WINDOWS=0 -D LOGGING=1 -Werror -Wall -Wextra -pedantic
DFLAGS=-fPIC -fanalyzer -D __CPP__=0 -D WINDOWS=0 -D LOGGING=1 -ggdb3 -Og -Werror -Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wredundant-decls -Wshadow -Wstrict-overflow=5 -Wundef -Wno-unused -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option
BFLAGS=-O3
LFLAGS=-ggdb3 -Og
OFLAGS=-fPIC -O3 -rdynamic

all:${ENGINE}

all : CFLAGS += ${DFLAGS}

${ENGINE}: ${ENGINEOBS}
	${CC} ${CFLAGS} -o $@ $^

engine.o: engine.c

.PHONY : clean

clean:
	rm -f ${ENGINE} core*
	rm -f *.o core*
