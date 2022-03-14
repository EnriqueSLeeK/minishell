/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:20:07 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/03/14 15:20:16 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_command	*parse_command(char *command)
{
	t_command	*new_command;
	char		**splitted;
	int			index;
	int			len;

	len = 0;
	new_command = (t_command *)ft_calloc(1, sizeof(t_command));
	splitted = ft_split(command, ' ');
	new_command->command = splitted[len];
	while (splitted[len])
		len++;
	new_command->args = ft_calloc(len, sizeof(char *));
	index = 1;
	while (index < len)
	{
		new_command->args[index - 1] = splitted[index];
		index++;
	}
	free(splitted);
	return (new_command);
}

void	create_new_command_node(t_command *new_command)
{
	t_command	*first;

	first = g_data.commands;
	while (first->next)
		first = first->next;
	new_command->previous = first;
	first->next = new_command;
}

void	create_command(char *command, char *relation)
{
	t_command	*first;
	t_command	*new_command;

	new_command = parse_command(command);
	new_command->input = STDIN_FILENO;
	new_command->output = STDOUT_FILENO;
	new_command->relation = relation;
	first = g_data.commands;
	if (first == NULL)
		g_data.commands = new_command;
	else
		create_new_command_node(new_command);
}

char	*create_node(char *line, int index, int first, char *relation)
{
	line[index] = '\0';
	index++;
	create_command(line, relation);
	line += index;
	if (first == TRUE)
	{
		while (*line && *line == ' ')
			line++;
	}
	return (line);
}
