/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 09:56:49 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/03/31 16:25:01 by mamaro-d         ###   ########.fr       */
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
	if (node->previous)
	{
		close_fd(node->previous->fd_in);
		close_fd(node->previous->fd_out);
	}
}