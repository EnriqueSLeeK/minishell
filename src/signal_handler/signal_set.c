/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:09:41 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/31 18:02:01 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	prompt_sig(t_signal *sig)
{
	signal_init(&(sig -> sig_int), SIGINT, interrupt_handler);
	signal_init(&(sig -> sig_quit), SIGQUIT, SIG_IGN);
}

void	exec_sig(t_signal *sig)
{
	signal_init(&(sig -> sig_int), SIGINT, exec_interrupt);
	signal_init(&(sig -> sig_quit), SIGQUIT, quit_sig);
}

void	child_sig(t_signal *sig)
{
	signal_init(&(sig -> sig_int), SIGINT, SIG_DFL);
	signal_init(&(sig -> sig_quit), SIGQUIT, SIG_DFL);
}
