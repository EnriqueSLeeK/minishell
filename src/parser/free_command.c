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

/* void	free_args(t_command *command)
{
	int	index;

	index = 0;
	while (command->args[index])
	{
		free(command->args[index]);
		index++;
	}
	free(command->args);
	free(command->relation);
	command->args = NULL;
}
*/
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
/*
void	free_commands(void)
{
	while (g_data.commands->next)
		g_data.commands = g_data.commands->next;
	while (g_data.commands->previous)
	{
		free_args(g_data.commands);
		g_data.commands = g_data.commands->previous;
		free(g_data.commands->next);
	}
	free_args(g_data.commands);
	free(g_data.commands);
	g_data.commands = NULL;
}
 */