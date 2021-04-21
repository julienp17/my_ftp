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
SRC_F		=	file_reading/get_file_size.c \
				file_reading/get_file_buffer.c \
				file_reading/get_nb_files_in_dir.c \
				file_reading/get_filenames_in_dir.c \
				file_reading/file_is_dir.c \
				client/client_create.c \
				client/client_destroy.c \
				server/server_create.c \
				server/server_run.c \
				server/server_destroy.c \
				server/log.c \
				server/tcp.c \
				server/accept_client.c \
				server/add_client.c \
				server/remove_client.c \
				server/send.c \
				server/handle_inputs.c \
				server/handle_cmd.c \
				server/get_data_sock.c \
				server/cmds/get_cmd.c \
				server/cmds/cmd_user.c \
				server/cmds/cmd_pass.c \
				server/cmds/cmd_quit.c \
				server/cmds/cmd_cwd.c \
				server/cmds/cmd_cdup.c \
				server/cmds/cmd_pwd.c \
				server/cmds/cmd_help.c \
				server/cmds/cmd_pasv.c \
				server/cmds/cmd_port.c \
				server/cmds/cmd_retr.c \
				server/cmds/cmd_noop.c \
				server/cmds/cmd_list.c \
				server/cmds/cmd_dele.c \

UT_SRC		=	$(addprefix $(UT_SRC_D), $(UT_SRC_F))
UT_OBJ		=	$(UT_SRC:.c=.o)
UT_SRC_D	=	tests/
UT_SRC_F	=	test_cmd_user.c \
				test_cmd_pass.c

CFLAGS		=	-W -Wall -Wextra -Werror $(INC) $(LDFLAGS)

INC			=	-I./inc

LDFLAGS		=	-L./lib/ -lmy

LDFLAGS_UT  =	-lcriterion --coverage

DBFLAGS		=	-g -g3 -ggdb

BIN			=	myftp

UT_BIN		=	unit_tests

all: $(BIN)

.PHONY: all
$(BIN): makelib $(OBJ_M) $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJ_M) $(OBJ) $(LDFLAGS)

makelib:
	make -C ./lib/my/ all

.PHONY: debug
debug: $(OBJ_M) $(OBJ)
	$(CC) $(CFLAGS) $(DBFLAGS) -o $(BIN) $(OBJ_M) $(OBJ) $(LDFLAGS)

.PHONY: tests_run
tests_run: clean $(OBJ) $(UT_OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS_UT) -o $(UT_BIN) $(OBJ) $(UT_OBJ) $(LDFLAGS)
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