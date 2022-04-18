/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 19:19:24 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/18 14:57:04 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
		child_clean_up(NULL);
		write(1, "\n", 1);
		exit(sig + 128);
	}
}
