/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:10:17 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/04/14 22:26:01 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	handle_red_output(t_node *node)
{
	t_node	*file;

	file = node->next;
	while (file->next && file->next->is_file)
	{
		close(open(file->args[0], O_CREAT | O_WRONLY | O_TRUNC, 0666));
		file = file->next;
	}
	node->fd_out = open(file->args[0], O_CREAT \
						| O_WRONLY | O_TRUNC, 0666);
}

void	handle_red_input(t_node *node)
{
	t_node	*file;

	file = node->next;
	while (file->next && !file->next->is_file)
	{
		node->fd_in = open(file->args[0], O_RDONLY);
		if (node->fd_in == -1)
			return ;
		close(node->fd_in);
		if (!file->next->is_file)
			break ;
		file = file->next;
	}
	node->fd_in = open(file->args[0], O_RDONLY);
}

//node->fd_in = here_doc_fd(node->next->args[0]);
void	handle_here_doc(t_node *node)
{
	pid_t	pid;

	pid = fork();
	here_doc_parent(&(g_data.sig));
	if (pid == 0)
	{
		here_doc_child(&(g_data.sig));
		here_doc_fd(node->next->args[0]);
		child_clean_up(0);
		exit(0);
	}
	wait(NULL);
	node->fd_in = open("/tmp/tmp_f", O_RDONLY);
}

int	handle_pipe(t_node *node)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (1);
	add_fd(fd[0]);
	add_fd(fd[1]);
	if (node->next)
		node->next->fd_in = fd[0];
	while (node && node->is_file)
		node = node->previous;
	if (node && node->fd_out == 1)
		node->fd_out = fd[1];
	else
		close(fd[1]);
	return (0);
}
