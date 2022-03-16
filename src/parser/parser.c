/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:05:26 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/03/16 11:26:01 by mamaro-d         ###   ########.fr       */
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



int	verify_infile(t_command *node)
{
	if(access(node->args[0], F_OK))
	{
		printf("file not exists\n");
		return (0);
	}
	return (1);
}

void link_relations()
{
	t_command *node;

	node = g_data.commands;
	while(node->next)
	{
		if(!ft_strncmp(node->relation, "|", ft_strlen(node->relation)))
			printf("command %s redirect output to %s\n", node->args[0], node->next->args[0]);
		else if(!ft_strncmp(node->relation, ">", ft_strlen(node->relation)))
			printf("command %s redirect output to file %s\n", node->args[0], node->next->args[0]);
		else if(!ft_strncmp(node->relation, "<", ft_strlen(node->relation)) && verify_infile(node->next))
			printf("command %s has input redirected to file %s\n", g_data.commands->args[0], node->next->args[0]);
		node = node->next;
		printf("\n\nNew node\n\n");
	}
}

void	toggle_quote(char *line, char *holder_quote)
{
	if(*line == QUOTE || *line == DOUBLE_QOUTE)
	{
		if(!*holder_quote)
			*holder_quote = *line;
		else if (*holder_quote && *line == *holder_quote)
			holder_quote = NULL;
	}
}

/* void fill_missing_arg(char *line, char *relation)
{
	char	**argv;
	char	*tmp;
	int		index;

	tmp = line;
	index = 0;
	while(!is_in(g_data.operators, &line[index]) && line[index])
		index++;
	line[index] == 0;
	while(!ft_isblank(*line) && *line != 0)
		line++;
	if(*line != 0)
	{
		argv = ft_split(line, ' ');
		g_data.commands->args = argv;
	}
} */

void	create_relation(char *line)
{
	char	*relation;
	int		index;
	int		first;
	char	holder_quote;

	index = 0;
	first = TRUE;
	while (line[index])
	{
		toggle_quote(&line[index], &holder_quote);
		relation = is_in(g_data.operators, &line[index]);
		if (relation)
		{
			line = create_node(line, index, first, relation);
			index = 0;
			first = FALSE;
		}
		index++;
	}
	if(*line != 0)
		create_node(line, index, first, relation);
	printf("address of next = %p", g_data.commands->next);
}
