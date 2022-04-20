# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/02 22:59:02 by ensebast          #+#    #+#              #
#    Updated: 2022/04/20 10:26:23 by mamaro-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
INCLUDE := -I ./include/

CC := gcc
CFLAGS :=  -Wall -Wextra -Werror -g
LIB := -lreadline

LIBFT := ./libft/libft.a

RM := rm -rf

# Source files
FILES_M := main.c\
	hash.c\
	pwd.c\
	cd.c\
	env.c\
	exit.c\
	find.c\
	echo.c\
	unset.c\
	export.c\
	prompt.c\
	convert.c\
	clean_up.c\
	misc_func.c\
	table_util.c\
	entry_util.c\
	search_bin.c\
	free_matrix.c\
	var_expansion.c\
	init_hash_table.c\
	create_local_var.c\
	status_expansion.c\
	micro_regex.c\
	expand.c\
	here_doc.c\
	parser_utils.c\
	handle_operators.c\
	exec_cmd.c\
	exec_utils.c\
	signal_handler.c\
	sig_here_doc.c\
	free_command.c\
	parser.c\
	signal_set.c\
	errors.c\
	we_pre_util_bonus.c\
	we_pre_split_bonus.c\
	file_list_bonus.c\
	wild_expansion_bonus.c\
	quotes.c

FILE_OBJ := $(FILES_M:c=o)
DIR_OBJ := ./obj/

OBJ_M := $(addprefix $(DIR_OBJ), $(FILE_OBJ))

VPATH := ./src/shell ./src/hash_table ./src/parser ./src/search_bin\
		 ./src/var_utils ./src/builtin ./src/executor ./src/misc_util\
		 ./src/signal_handler ./src/var_utils/wildcard_util

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
