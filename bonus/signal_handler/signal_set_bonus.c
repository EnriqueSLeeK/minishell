/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_set_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:09:41 by ensebast          #+#    #+#             */
/*   Updated: 2022/05/14 15:14:24 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_bonus.h"

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

void	here_doc_parent(t_signal *sig)
{
	signal_init(&(sig -> sig_int), SIGINT, interrupt_here_doc);
}

void	here_doc_child(t_signal *sig)
{
	signal_init(&(sig -> sig_int), SIGINT, int_here_doc_child);
}
