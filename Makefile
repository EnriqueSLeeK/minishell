# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/02 22:59:02 by ensebast          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2022/03/15 13:26:52 by mamaro-d         ###   ########.fr        #
=======
#    Updated: 2022/03/15 18:16:03 by ensebast         ###   ########.fr        #
>>>>>>> 34bd3c4baf737e09af25de6a765ee209908d5b44
#                                                                              #
# **************************************************************************** #

NAME := minishell
INCLUDE := -I ./include/

CC := gcc
CFLAGS :=  -g -Wall -Wextra -Werror
LIB := -lreadline

LIBFT := ./libft/libft.a

RM := rm -rf

# Source files
FILES_M := main.c\
	hash.c\
	echo.c\
	pwd.c\
	cd.c\
	env.c\
	unset.c\
	export.c\
	prompt.c\
	clean_up.c\
	misc_func.c\
	table_util.c\
	entry_util.c\
	search_bin.c\
	var_expansion.c\
	init_hash_table.c\
	create_local_var.c\
	create_command.c\
	free_command.c\
	parser.c
	

FILE_OBJ := $(FILES_M:c=o)
DIR_OBJ := ./obj/

OBJ_M := $(addprefix $(DIR_OBJ), $(FILE_OBJ))

VPATH := ./src/shell ./src/hash_table ./src/parser ./src/search_bin ./src/var_utils
$(DIR_OBJ)%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -c $^ -o $@

$(NAME): $(OBJ_M) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJ_M) $(LIBFT) $(LIB)

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
