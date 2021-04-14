##
## EPITECH PROJECT, 2021
## my_ftp
## File description:
## Makefile
##

CC			=	gcc

MAIN		=	$(addprefix $(SRC_D), main.c)
OBJ_M		=	$(MAIN:.c=.o)

SRC			=	$(addprefix $(SRC_D), $(SRC_F))
OBJ			=	$(SRC:.c=.o)
SRC_D		=	src/
SRC_F		=	server/server_create.c \
				server/server_run.c \
				server/server_destroy.c \
				server/accept_client.c \
				server/handle_inputs.c \
				server/handle_cmd.c \
				socket/socket_create.c

UT_SRC		=	$(addprefix $(UT_SRC_D), $(UT_SRC_F))
UT_OBJ		=	$(UT_SRC:.c=.o)
UT_SRC_D	=	tests/
UT_SRC_F	=

CFLAGS		=	-W -Wall -Wextra -Werror $(INC) $(LDFLAGS)

INC			=	-I./inc

LDFLAGS		=

LDFLAGS_UT  =	-lcriterion --coverage

DBFLAGS		=	-g -g3 -ggdb

BIN			=	myftp

UT_BIN		=	unit_tests

all: $(BIN)

.PHONY: all
$(BIN): $(OBJ_M) $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJ_M) $(OBJ)

.PHONY: debug
debug: $(OBJ_M) $(OBJ)
	$(CC) $(CFLAGS) $(DBFLAGS) -o $(BIN) $(OBJ_M) $(OBJ)

.PHONY: tests_run
tests_run: clean $(OBJ) $(UT_OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS_UT) -o $(UT_BIN) $(OBJ) $(UT_OBJ)
	./$(UT_BIN)

.PHONY: functional_tests
functional_tests:
	./tests/functional/functional_tests.sh

.PHONY: coverage
coverage:
	gcovr -r . --exclude-directories tests
	gcovr -b --exclude-directories tests

.PHONY: clean
clean:
	rm -f $(OBJ)
	rm -f $(OBJ_M)
	rm -f $(OBJ_UT)
	rm -f *.gc*

.PHONY: fclean
fclean: clean
	rm -f $(BIN)
	rm -f $(BIN_UT)

.PHONY: re
re: fclean all