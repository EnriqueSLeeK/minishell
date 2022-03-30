/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 23:36:29 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/30 13:15:54 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

# include <signal.h>

typedef struct s_signal
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;
}	t_signal;

void	quit_sig(int sig);
void	exit_code(int sig);
void	interrupt_handler(int sig);
void	signal_init(struct sigaction *act, int sig, void handler(int));

// Initializers
void	prompt_sig(t_signal *sig);
void	child_sig(t_signal *sig);
void	exec_sig(t_signal *sig);

#endif
