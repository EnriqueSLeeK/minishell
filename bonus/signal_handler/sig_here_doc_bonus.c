/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_here_doc_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 19:19:24 by ensebast          #+#    #+#             */
/*   Updated: 2022/05/14 15:14:24 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_bonus.h"

void	interrupt_here_doc(int sig)
{
	if (SIGINT == sig)
	{
		g_data.status = CANCEL;
		exit_code(sig);
	}
}

void	int_here_doc_child(int sig)
{
	if (SIGINT == sig)
	{
		write(1, "\n", 1);
		child_clean_up(NULL, sig + 128);
	}
}
