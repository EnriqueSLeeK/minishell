/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:08:00 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/03 00:22:29 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	init_signal(void);
static void	signal_handler(int sig);

int	main(void)
{
	char	*line;

	init_signal();
	while (1)
	{
		line = prompt();
		free(line);
	}
	return (0);
}

// SIGQUIT = ctrl + d must be ignored
// SIGINT = ctrl + c will call the function signal_handler
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
