/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:05:26 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/03/15 10:20:26 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


/* 	Verify if the first characters of line is equal of an operator
	and returns a operator as relation for the next command
*/
static char	*is_in(char **operators, char *line)
{
	while (*operators)
	{
		if (!ft_strncmp(*operators, line, ft_strlen(*operators)))
			return (*operators);
		operators++;
	}
	return (NULL);
}

/*
void	print_commands(void)
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
}*/

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
}
