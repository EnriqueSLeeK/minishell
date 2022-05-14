/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 10:08:19 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/05/14 15:27:08 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_BONUS_H
# define EXECUTOR_BONUS_H

# include "shell_bonus.h"

void	add_fd(int fd);
void	close_fd(int fd);
void	close_prev_fd(t_node *node);
void	free_fds(void);
void	exec_extern_cmd(t_node *node);
void	execute_cmd(t_node *node);
void	exec_commands(void);
int		exec_bultin(t_node *node);
void	verify_node(t_node *node, int *status);

int		check_grammar(void);
void	link_relation(void);

// Here doc
int		here_doc_fd(char *delim);
#endif
