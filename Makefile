# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/02 22:59:02 by ensebast          #+#    #+#              #
#    Updated: 2022/03/03 15:55:15 by ensebast         ###   ########.br        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
INCLUDE := -I ./include/

CC := clang
CFLAGS := -Wall -Werror -Wextra
LIB := -lreadline

RM := rm -rf

FILES_M := main.c prompt.c
DIR_M := ./src/

FILE_OBJ := $(FILES_M:c=o)
DIR_OBJ := ./obj/

OBJ_M := $(addprefix $(DIR_OBJ), $(FILE_OBJ))
SRC_M := $(addprefix $(DIR_M), $(FILES_M))

DIR_GUARD=@mkdir -p $(@D)

$(DIR_OBJ)%.o: $(DIR_M)%.c
	$(DIR_GUARD)
	$(CC) $(INCLUDE) -c $^ -o $@

$(NAME): $(OBJ_M) ./include/shell.h
	$(CC) -o $@ $(OBJ_M) $(LIB)

all: $(NAME)

clean:
	$(RM) $(DIR_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
