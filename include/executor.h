/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 10:08:19 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/04/23 10:44:05 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "shell.h"

void	add_fd(int fd);
void	close_fd(int fd);
void	close_prev_fd(t_node *node);
void	free_fds(void);
void	exec_extern_cmd(t_node *node);
void	execute_cmd(t_node *node);
void	exec_commands(void);

int		check_grammar(void);

// Here doc
int		here_doc_fd(char *delim);
#endif
