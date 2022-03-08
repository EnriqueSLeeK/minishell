/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:08:00 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/07 23:25:03 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_shell	g_data;

static void	init_signal(void);
static void	interrupt_handler(int sig);
static void	init(char *envp[]);

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;

	init(envp);
	while (1)
	{
		line = prompt();
		free(line);
	}
	return (0);
}

void	init(char *envp[])
{
	init_signal();
	init_env_table(envp);
}

// SIGQUIT = ctrl + \ must be ignored
// SIGINT = ctrl + c will call the function interrupt_handler
static void	init_signal(void)
{
	signal(SIGINT, interrupt_handler);
	signal(SIGQUIT, SIG_IGN);
}

static void	interrupt_handler(int sig)
{
	write(1, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}
