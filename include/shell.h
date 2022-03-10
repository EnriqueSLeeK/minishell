/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:46:35 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/10 18:27:12 by ensebast         ###   ########.br       */
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
# include "hash_table.h"
# include "../libft/libft.h"

typedef struct s_shell
{
	t_hash_table	*env_vars;
	t_hash_table	*local_vars;
	int				exit_code;
}	t_shell;

extern t_shell	g_data;

// Prompt
char	*prompt(void);
void	clean_up(void);
int		init_env_table(char *envp[]);

#endif
