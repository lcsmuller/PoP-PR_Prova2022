CC ?= gcc

EXES = questao1 questao2 questao3 questao4

CFLAGS = -g -Wall -Wextra -Wpedantic

# Utilizamos de 'regras implícitas' da Makefile para compilar os executáveis:
# https://ftp.gnu.org/old-gnu/Manuals/make-3.79.1/html_chapter/make_10.html
all: $(EXES)

clean:
	@ $(RM) $(EXES)

.PHONY: all clean
