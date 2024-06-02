CC=gcc
LINK=gcc

OCCLUSION=occlusiontest

OCCLUSIONOBS=occlusiontest.o occlusion.o memory.o

LIBS=-lm
CFLAGS=-fPIC -D WINDOWS=0 -D LOGGING=1 -Werror -Wall -Wextra -pedantic
DFLAGS=-fPIC -fanalyzer -D WINDOWS=0 -D LOGGING=1 -ggdb3 -Og -Werror -Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wredundant-decls -Wshadow -Wstrict-overflow=5 -Wundef -Wno-unused -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option
BFLAGS=-O3
LFLAGS=-ggdb3 -Og
OFLAGS=-fPIC -O3 -rdynamic

all:${OCCLUSION}

all : CFLAGS += ${BFLAGS}

${OCCLUSION}: ${OCCLUSIONOBS}
	${CC} -o $@ $^

memory.o: memory.c
occlusion.o: occlusion.c
occlusiontest.o: occlusiontest.c

.PHONY : clean

clean:
	rm -f ${OCCLUSION} core*
	rm -f *.o core*
