/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:19:19 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/04/13 11:16:13 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	free_args(t_node *node)
{
	int	index;

	index = 0;
	while (node->args[index])
	{
		free(node->args[index]);
		node->args[index] = NULL;
		index++;
	}
	free(node->args);
	node->args = NULL;
}

void	free_operations(void)
{
	int	index;

	index = 0;
	while (index < 7)
	{
		free(g_data.operators[index]);
		g_data.operators[index] = NULL;
		index++;
	}
	free(g_data.operators);
	g_data.operators = NULL;
}

void	free_commands_from_last(void)
{
	while (g_data.node->previous)
	{
		free_args(g_data.node);
		if (g_data.node->fd_in != 0 && g_data.node->fd_in != -1)
			close(g_data.node->fd_in);
		if (g_data.node->fd_out != 1)
			close(g_data.node->fd_out);
		g_data.node = g_data.node->previous;
		free(g_data.node->next);
	}
}

void	free_commands(void)
{
	if (!g_data.node)
		return ;
	while (g_data.node->next)
		g_data.node = g_data.node->next;
	free_commands_from_last();
	if (g_data.node->fd_in != 0 && g_data.node->fd_in != -1)
		close(g_data.node->fd_in);
	if (g_data.node->fd_out != 1)
		close(g_data.node->fd_out);
	free_args(g_data.node);
	free(g_data.node);
	g_data.node = NULL;
}
