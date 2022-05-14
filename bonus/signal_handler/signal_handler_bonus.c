/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 01:44:47 by ensebast          #+#    #+#             */
/*   Updated: 2022/05/14 15:14:24 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_bonus.h"

void	quit_sig(int sig)
{
	write(1, "Quit\n", 5);
	if (SIGQUIT == sig)
		exit_code(sig);
}

void	interrupt_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		exit_code(sig);
	}
}

void	exec_interrupt(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		exit_code(sig);
	}
}

void	exit_code(int sig)
{
	g_data.exit_code = sig + 128;
}

void	signal_init(struct sigaction *act, int sig, void handler(int))
{
	act -> sa_handler = handler;
	act -> sa_flags = SA_RESTART;
	sigemptyset(&(act -> sa_mask));
	sigaction(sig, act, 0);
}
