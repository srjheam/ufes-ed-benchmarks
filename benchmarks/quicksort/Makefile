# BUILDIR        - é o diretório onde estarão os binários
# LIBBENCHDIR   - é o diretório para a biblioteca de tipos comuns.
# LIBBENCH      - é a biblioteca de tipos comuns.
LIBBENCHDIR     = ../lib
LIBBENCHINCLUDE = $(LIBBENCHDIR)
LIBBENCH        = bench
VALGRINDOUT     = valgrind-out.txt
MAIN            = main

# CCompiler - é o compilador usado
# CFLAGS    - são as flags dadas ao compilador durante a compilação
CC = gcc
override CFLAGS += -Wall -Wall -Wextra -Werror -pedantic -ggdb3 -I$(LIBBENCHINCLUDE) -lm

# Make - é o GNU Make
MAKE = make

all : build

# Chama os submakefiles garantindo a compilação das bibliotecas
pre-build:
	$(MAKE) -C $(LIBBENCHDIR)/

build : main.c pre-build
	$(CC) -o $(MAIN) $< -L $(LIBBENCHDIR)/ -l$(LIBBENCH) $(CFLAGS)

# Rode make clean para remover tudo que é gerado pela build
clean:
	rm -f $(MAIN) $(VALGRINDOUT)
	$(MAKE) -C $(LIBBENCHDIR)/ clean

valgrind: all
	rm -f $(VALGRINDOUT)

	valgrind --leak-check=full \
			 --show-leak-kinds=all \
			 --track-origins=yes \
			 --verbose \
			 --log-file=$(VALGRINDOUT) \
			 ./$(MAIN) $(VALARGS)

	@echo "Head to $(VALGRINDOUT)"