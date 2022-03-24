/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 23:22:20 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/24 01:17:10 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	quit_sig(int sig)
{
	write(1, "Quit\n", 5);
	if (SIGQUIT == sig && (g_data.status & EXEC_STATUS))
		g_data.exit_code = 131;
}

void	interrupt_handler(int sig)
{
	write(1, "\n", 1);
	if (sig == SIGINT && !(g_data.status & EXEC_STATUS))
	{
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_data.exit_code = 130;
	}
	g_data.exit_code = 130;
}

void	signal_init(struct sigaction *act, int sig, void handler(int))
{
	act -> sa_handler = handler;
	act -> sa_flags = SA_RESTART;
	sigemptyset(&(act -> sa_mask));
	sigaction(sig, act, 0);
}
