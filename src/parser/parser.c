/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:05:26 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/03/14 14:45:32 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*is_in(char **operators, char *line)
{
	while (*operators)
	{
		if (!ft_strncmp(*operators, line, ft_strlen(*operators)))
			return (*operators);
		operators++;
	}
	return (NULL);
}

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

/* void	print_commands(void)
{
	int	index;
	index = -1;
	t_command *first;

	first = g_data.commands;	
	printf("command\targs\trelation\tnext\n");
	while (g_data.commands)
	{
		printf("%s\t", g_data.commands->command);
		while (g_data.commands->args[++index])
			printf("%s ", g_data.commands->args[index]);
		printf("\t%s\t", g_data.commands->relation);
		if(g_data.commands->next)
			printf("%s", g_data.commands->next->command);
		g_data.commands = g_data.commands->next;
		index = 0;
		printf("\n");
	}
	g_data.commands = first;
} */

void	free_args(t_command *command)
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
	free(command->command);
	command->args = NULL;
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
	free_operations();
}

void	create_relation(char *line)
{
	char	*relation;
	int		index;
	int		first;

	index = 0;
	first = TRUE;
	while (line[index])
	{
		relation = is_in(g_data.operators, &line[index]);
		if (relation)
		{
			line = create_node(line, index, first, relation);
			index = 0;
			first = FALSE;
		}
		index++;
	}
	line = create_node(line, index, first, relation);
	print_commands();
	free_commands();
}
