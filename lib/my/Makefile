##
## EPITECH PROJECT, 2019
## Pushswap
## File description:
## Libmy Makefile
##

CC 		= 	gcc

SRC		=	my_str_isnum_pos.c \
			my_str_toupper.c \
			my_strdupcat.c

OBJ		=	$(SRC:.c=.o)

CFLAGS	=	-W -Wall -Wextra -Werror

DBFLAGS	=	-g -g3 -ggdb

HEADER	=	my.h

NAME	=	libmy.a

all:		$(OBJ)
			ar rc $(NAME) $(OBJ)
			cp $(NAME) ../
			cp $(HEADER) ../../inc

clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)
			rm -f ../$(NAME)
			rm -f ../../inc/$(HEADER)

re:			fclean all

.phony:		re fclean clean
