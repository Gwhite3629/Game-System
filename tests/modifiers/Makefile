CC=gcc
LINK=gcc

RELPATH=../../

OCCLUSION=occlusiontest

OCCLUSIONOBS=$(RELPATH)src/utils/memory.o $(RELPATH)src/utils/hash.o $(RELPATH)src/modifiers/occlusion.o occlusiontest.o 

LIBS=-lm -I$(RELPATH)include
CFLAGS=-fPIC -D WINDOWS=0 -D LOGGING=1 -Werror -Wall -Wextra -pedantic
DFLAGS=-fPIC -fanalyzer -D __CPP__=0 -D WINDOWS=0 -D LOGGING=1 -ggdb3 -Og -Werror -Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wredundant-decls -Wshadow -Wstrict-overflow=5 -Wundef -Wno-unused -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option
BFLAGS=-O3
LFLAGS=-ggdb3 -Og
OFLAGS=-fPIC -O3 -rdynamic

all:${OCCLUSION}

all : CFLAGS += ${DFLAGS} ${LIBS}

${OCCLUSION}: ${OCCLUSIONOBS}
	${CC} ${CFLAGS} -o $@ $^

memory.o: $(RELPATH)src/utils/memory.c
hash.o: $(RELPATH)src/utils/hash.c
occlusion.o: $(RELPATH)src/modifiers/occlusion.c
occlusiontest.o: occlusiontest.c

.PHONY : clean

clean:
	rm -f ${OCCLUSION} core*
	rm -f ${OCCLUSIONOBS} core*
