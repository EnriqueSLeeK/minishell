# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/02 22:59:02 by ensebast          #+#    #+#              #
#    Updated: 2022/05/28 15:21:19 by ensebast         ###   ########.br        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

INCLUDE := -I ./include/
INCLUDE_B := -I ./bonus/include/

CC := gcc
LIB := -lreadline
CFLAGS :=  -Wall -Wextra -Werror -g

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

FILE_B := cd_bonus.c\
	echo_bonus.c\
	env_bonus.c\
	exit_bonus.c\
	export_bonus.c\
	pwd_bonus.c\
	unset_bonus.c\
	exec_cmd_bonus.c\
	exec_helper_bonus.c\
	exec_utils_bonus.c\
	here_doc_bonus.c\
	entry_util_bonus.c\
	hash_bonus.c\
	init_hash_table_bonus.c\
	misc_func_bonus.c\
	table_util_bonus.c\
	convert_bonus.c\
	find_bonus.c\
	free_matrix_bonus.c\
	micro_regex_bonus.c\
	quote_res_bonus.c\
	skip_segment_bonus.c\
	free_command_bonus.c\
	handle_operators_bonus.c\
	handle_operator_2_bonus.c\
	parser_bonus.c\
	parser_quotes_helper_bonus.c\
	parser_utils_bonus.c\
	relations_bonus.c\
	string_utils_bonus.c\
	search_bin_bonus.c\
	clean_up_bonus.c\
	errors_bonus.c\
	main_bonus.c\
	prompt_bonus.c\
	sig_here_doc_bonus.c\
	signal_handler_bonus.c\
	signal_set_bonus.c\
	create_local_var_bonus.c\
	expand_bonus.c\
	expand_util_bonus.c\
	status_expansion_bonus.c\
	var_expansion_bonus.c\
	file_list_bonus.c\
	file_list_util_bonus.c\
	we_pre_split_bonus.c\
	we_pre_util_bonus.c\
	wild_expansion_bonus.c

FILE_OBJ := $(FILES_M:c=o)
FILE_OBJ_BONUS := $(FILE_B:c=o)

DIR_OBJ := ./obj/

OBJ_M := $(addprefix $(DIR_OBJ), $(FILE_OBJ))
OBJ_B := $(addprefix $(DIR_OBJ), $(FILE_OBJ_BONUS))

VPATH := ./src/shell ./src/hash_table ./src/parser ./src/search_bin\
		 ./src/var_utils ./src/builtin ./src/executor ./src/misc_util\
		 ./src/signal_handler\
		 ./bonus/var_utils/wildcard_util ./bonus/shell ./bonus/hash_table\
		 ./bonus/parser ./bonus/search_bin ./bonus/var_utils ./bonus/builtin\
		 ./bonus/executor ./bonus/misc_util ./bonus/signal_handler

all: $(OBJ_M) $(NAME)

bonus: $(OBJ_B) $(NAME)

$(DIR_OBJ)%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE_B) $(INCLUDE) -c $^ -o $@

$(LIBFT):
	make -C libft

$(NAME): $(DIR_OBJ) $(LIBFT)
	test -f obj/main_bonus.o || \
		$(CC) $(CFLAGS) -o $@ $(OBJ_M) $(LIBFT) $(LIB);
	(test -f obj/main_bonus.o && \
		$(CC) $(CFLAGS) -o $@ $(OBJ_B) $(LIBFT) $(LIB)) || true;

clean:
	$(RM) $(DIR_OBJ)
	make clean -C libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re bonus
