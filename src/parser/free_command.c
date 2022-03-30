/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:19:19 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/03/22 12:07:52 by mamaro-d         ###   ########.fr       */
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
		index++;
	}
	free(node->args);
	free(node->relation);
	node->args = NULL;
}

void	free_operations(void)
{
	int	index;

	index = 0;
	while (g_data.operators[index])
	{
		free(g_data.operators[index]);
		index++;
	}
	free(g_data.operators);
	g_data.operators = NULL;
}

void	free_commands(void)
{
	while (g_data.node->next)
		g_data.node = g_data.node->next;
	while (g_data.node->previous)
	{
		free_args(g_data.node);
		g_data.node = g_data.node->previous;
		free(g_data.node->next);
	}
	free_args(g_data.node);
	free(g_data.node);
	g_data.node = NULL;
}
