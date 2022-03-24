/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 23:36:29 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/24 01:25:43 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

# define READ_STATUS 0
# define EXEC_STATUS 1
# define HERE_DOC_STATUS 2

# include <signal.h>

void	quit_sig(int sig);
void	interrupt_handler(int sig);
void	signal_init(struct sigaction *act, int sig, void handler(int));

#endif
