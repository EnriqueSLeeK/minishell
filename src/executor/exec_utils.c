/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 09:56:49 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/04/25 10:21:20 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	free_fds(void)
{
	t_fd	*tmp;

	tmp = g_data.fds;
	while (tmp)
	{
		g_data.fds = g_data.fds->next;
		free(tmp);
		tmp = g_data.fds;
	}
}

void	add_fd(int fd)
{
	t_fd	*new_fd;
	t_fd	*last_fd;

	if (fd == -1)
		return ;
	new_fd = (t_fd *)ft_calloc(sizeof(t_fd), 1);
	new_fd->value = fd;
	last_fd = g_data.fds;
	if (last_fd == NULL)
		g_data.fds = new_fd;
	else
	{
		while (last_fd->next)
			last_fd = last_fd->next;
		last_fd->next = new_fd;
	}
}

void	close_fd(int fd)
{
	t_fd	*fds;

	if (fd == STDIN_FILENO || fd == STDOUT_FILENO)
		return ;
	fds = g_data.fds;
	while (fds)
	{
		if (fds->value == fd)
			close(fds->value);
		fds = fds->next;
	}
}

void	close_prev_fd(t_node *node)
{
	if (node->previous && !node->previous->is_file)
	{
		if (node->previous->fd_in != 0)
			close_fd(node->previous->fd_in);
		if (node->previous->fd_out != 1)
			close_fd(node->previous->fd_out);
	}
}

void	link_relation(void)
{
	t_node	*node;

	node = g_data.node;
	while (node)
	{
		if (node->relation && !node->next)
			return ;
		if (node->relation && ft_strncmp(node->relation, " ", 1))
		{
			if (!ft_strncmp(node->relation, "|", 1))
				handle_pipe(node);
			else if (!ft_strncmp(node->relation, "<<", 2))
				handle_here_doc(node);
			else if (!ft_strncmp(node->relation, ">>", 2))
				handle_red_output(node);
			else if (!ft_strncmp(node->relation, ">", 1))
				handle_red_output(node);
			else if (!ft_strncmp(node->relation, "<", 1))
				handle_red_input(node);
			else
				show_error(M_ERROR_SYNTAX, "'newline'", 2, 0);
		}
		node = node->next;
	}
	return ;
}
