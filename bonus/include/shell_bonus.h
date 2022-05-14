/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:46:35 by ensebast          #+#    #+#             */
/*   Updated: 2022/05/14 15:26:55 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_BONUS_H
# define SHELL_BONUS_H

// System headers
# include <stdio.h>
# include <unistd.h>
# include <dirent.h>
# include <signal.h>
# include <stdlib.h>
# include <termios.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>

// Custom project headers
# include "misc_func_bonus.h"
# include "builtin_bonus.h"
# include "bin_var_bonus.h"
# include "signal_handler_bonus.h"
# include "hash_table_bonus.h"
# include "parser_bonus.h"
# include "executor_bonus.h"
# include "wildcard_bonus.h"
# include "../../libft/libft.h"

/* Error messages */
# define M_COMMAND_NOT_FOUND "command not found "
# define M_INVALID_FILE "No such file or directory"
# define M_ERROR_SYNTAX "syntax error near unexpected token "
# define M_PERMISSION "Permission denied"
# define M_QUOTES_ERROR "unexpected EOF while looking for matching `\"' "
# define M_PAR_ERROR "unexpected EOF while looking for matching ( or )"
# define M_SYNTAX_EOF "syntax error: unexpected end of file"

typedef struct s_shell_bonus
{
	char			*line;
	t_hash_table	*env_vars;
	t_hash_table	*local_vars;
	t_node			*node;
	t_fd			*fds;
	int				status;
	int				exit_code;
	char			**operators;
	char			**envp;
	t_signal		sig;
}	t_shell_bonus;

extern t_shell_bonus	g_data;

// Prompt
char	*prompt(void);

// Convert hash_table to char **
char	**convert_table_matrix(t_hash_table *table);

// Clean up
void	clean_up(void);
void	child_clean_up(char **envp, int exit_code);
void	post_exec_clean(char *line);

// init env table
int		init_env_table(char *envp[]);

//Error Handler
void	show_error(char *name, char *message, int status, int exit_from_shell);

//Convert exit Status
int		get_status(int status);

#endif
