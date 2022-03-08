# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/02 22:59:02 by ensebast          #+#    #+#              #
#    Updated: 2022/03/07 23:08:24 by ensebast         ###   ########.br        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
INCLUDE := -I ./include/

CC := clang
CFLAGS := -Wall -Werror -Wextra
LIB := -lreadline

LIBFT := ./libft/libft.a

RM := rm -rf

FILES_M := main.c\
	hash.c\
	prompt.c\
	clean_up.c\
	misc_func.c\
	table_util.c\
	entry_util.c\
	init_hash_table.c

FILE_OBJ := $(FILES_M:c=o)
DIR_OBJ := ./obj/

OBJ_M := $(addprefix $(DIR_OBJ), $(FILE_OBJ))

VPATH := ./src/shell ./src/hash_table

$(DIR_OBJ)%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(INCLUDE) -c $^ -o $@

$(NAME): $(OBJ_M) $(LIBFT)
	$(CC) -o $@ $(OBJ_M) $(LIBFT) $(LIB)

$(LIBFT):
	make -C libft

all: $(NAME)

clean:
	$(RM) $(DIR_OBJ)
	make clean -C libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
