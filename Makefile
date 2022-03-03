# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/02 22:59:02 by ensebast          #+#    #+#              #
#    Updated: 2022/03/02 23:31:11 by ensebast         ###   ########.br        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
INCLUDE := -I ./include/

CC := clang
CFLAGS := -Wall -Werror -Wextra
LIB := -lreadline

RM := rm -rf

PROMPT := prompt.c -lreadline

FILES_M := main.c 
DIR_M := ./src/

FILE_OBJ := $(FILES_M:c=o)
DIR_OBJ := ./obj/

OBJ_M := $(addprefix $(DIR_OBJ), $(FILE_OBJ))
SRC_M := $(addprefix $(DIR_M), $(FILES_M))

DIR_GUARD=@mkdir -p $(@D)

$(DIR_OBJ)%.o: $(DIR_M)%.c
	$(DIR_GUARD)
	$(CC) $(INCLUDE) -c $^ -o $@

$(DIR_OBJ)%.o: $(DIR_M)prompt.c
	$(DIR_GUARD)
	$(CC) $(INCLUDE) -c $(PROMPT) -o $@

$(NAME): $(OBJ_M) ./include/shell.h $(DIR_OBJ)prompt.o
	$(CC) -o $@ $(OBJ_M) $(DIR_OBJ)prompt.o $(LIB)

all: $(NAME)

clean:
	$(RM) $(DIR_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
