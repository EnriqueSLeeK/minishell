/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:46:35 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/24 00:41:21 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

// System headers
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <termios.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/types.h>
# include <sys/wait.h>

// Custom project headers
# include "misc_func.h"
# include "builtin.h"
# include "bin_var.h"
# include "signal_handler.h"
# include "hash_table.h"
# include "parser.h"
# include "executor.h"
# include "../libft/libft.h"

typedef struct s_shell
{
	t_hash_table		*env_vars;
	t_hash_table		*local_vars;
	int					exit_code;
	int					status;
	char				**operators;
	t_command			*commands;
	t_fd				*all_fd;
	struct sigaction	sint_inf;
	struct sigaction	squit_inf;
}	t_shell;

extern t_shell	g_data;

// Prompt
char	*prompt(void);
void	clean_up(void);
int		init_env_table(char *envp[]);

#endif
