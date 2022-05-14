/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler_bonus.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 23:36:29 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/14 22:15:13 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

# include <signal.h>

# define CANCEL 0
# define CONTINUE 1

typedef struct s_signal
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;
}	t_signal;

// Signal handlers
void	quit_sig(int sig);
void	exit_code(int sig);
void	exec_interrupt(int sig);
void	interrupt_handler(int sig);
void	signal_init(struct sigaction *act, int sig, void handler(int));

// Signal for here_doc
void	interrupt_here_doc(int sig);
void	int_here_doc_child(int sig);

// Initializers
void	prompt_sig(t_signal *sig);
void	child_sig(t_signal *sig);
void	exec_sig(t_signal *sig);
// Here_doc set signals
void	here_doc_parent(t_signal *sig);
void	here_doc_child(t_signal *sig);
#endif
