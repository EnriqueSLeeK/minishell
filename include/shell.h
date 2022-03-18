/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:46:35 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/17 15:36:03 by mamaro-d         ###   ########.fr       */
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

// Custom project headers
# include "builtin.h"
# include "bin_var.h"
# include "hash_table.h"
# include "parser.h"
# include "executor.h"
# include "../libft/libft.h"

typedef struct s_shell
{
	t_hash_table	*env_vars;
	t_hash_table	*local_vars;
	int				exit_code;
	char			**operators;
	t_command		*commands;
	t_fd			*all_fds;
}	t_shell;

extern t_shell	g_data;

// Prompt
char	*prompt(void);
void	clean_up(void);
int		init_env_table(char *envp[]);

#endif
