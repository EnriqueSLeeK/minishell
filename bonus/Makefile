# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/02 22:59:02 by ensebast          #+#    #+#              #
#    Updated: 2022/05/02 21:28:14 by ensebast         ###   ########.br        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
INCLUDE := -I ../include/

CC := gcc
CFLAGS :=  -Wall -Wextra -Werror -g
LIB := -lreadline

LIBFT := ../libft/libft.a

RM := rm -rf

FILE_B := main.c\
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
	expand.c\
	here_doc.c\
	parser_utils.c\
	handle_operators.c\
	exec_cmd.c\
	quote_res.c\
	exec_utils.c\
	signal_handler.c\
	skip_segment.c\
	sig_here_doc.c\
	free_command.c\
	parser_quotes_helper.c\
	parser.c\
	string_utils.c\
	signal_set.c\
	expand_util.c\
	errors.c\
	file_list_bonus.c\
	file_list_util_bonus.c\
	we_pre_split_bonus.c\
	we_pre_util_bonus.c\
	micro_regex_bonus.c\
	wild_expansion_bonus.c

FILE_OBJ := $(FILES_M:c=o)
DIR_OBJ := ./obj/

FILE_OBJ_BONUS := $(FILE_B:c=o)
DIR_OBJ_BONUS := ./obj_bonus/

OBJ_M := $(addprefix $(DIR_OBJ), $(FILE_OBJ))
OBJ_B := $(addprefix $(DIR_OBJ_BONUS), $(FILE_OBJ_BONUS))

VPATH := ./shell ./hash_table ./parser ./search_bin\
		 ./var_utils ./builtin ./executor ./misc_util\
		 ./signal_handler ./var_utils/wildcard_util

$(DIR_OBJ)%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -c $^ -o $@

$(DIR_OBJ_BONUS)%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -c $^ -o $@

$(NAME): $(OBJ_M) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJ_M) $(LIBFT) $(LIB)

$(LIBFT):
	make -C ../libft

all: $(NAME)

bonus: $(OBJ_B) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_B) $(LIBFT) $(LIB)

clean:
	$(RM) $(DIR_OBJ)
	$(RM) $(DIR_OBJ_BONUS)
	make clean -C ../libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C ../libft

re: fclean all

.PHONY: all clean fclean re bonus
