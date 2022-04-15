/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:46:35 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/14 21:11:00 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

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
# include "misc_func.h"
# include "builtin.h"
# include "bin_var.h"
# include "signal_handler.h"
# include "hash_table.h"
# include "parser.h"
# include "executor.h"
# include "wildcard_bonus.h"
# include "../libft/libft.h"

/* Error messages */
# define M_COMMAND_NOT_FOUND ": command not found"
# define M_INVALID_FILE ": No such file or directory"
# define M_ERROR_SYNTAX "syntax error near unexpected token "
# define M_PERMISSION ": Permission denied"

typedef struct s_shell
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
}	t_shell;

extern t_shell	g_data;

// Prompt
char	*prompt(void);

// Convert hash_table to char **
char	**convert_table_matrix(t_hash_table *table);

// Clean up
void	clean_up(void);
void	child_clean_up(char **envp);
void	post_exec_clean(char *line);

// init env table
int		init_env_table(char *envp[]);

//Error Handler
void	show_error(char *name, char *message, int status, int exit_from_shell);

#endif
