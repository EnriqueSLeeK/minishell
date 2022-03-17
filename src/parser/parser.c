/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:05:26 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/03/17 10:20:39 by mamaro-d         ###   ########.fr       */
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

int	is_builtin(t_command *cmd)
{
	if (!cmd->args[0])
		return (cmd->builtin = FALSE);
	if (!(ft_strncmp(cmd->args[0], "exit", 4)))
		return (cmd->builtin =  TRUE);
	if (!(ft_strncmp(cmd->args[0], "cd", 2)))
		return (cmd->builtin =  TRUE);
	if (!(ft_strncmp(cmd->args[0], "pwd", 3)))
		return (cmd->builtin =  TRUE);
	if (!(ft_strncmp(cmd->args[0], "export", 6)))
		return (cmd->builtin =  TRUE);
	if (!(ft_strncmp(cmd->args[0], "env", 3)))
		return (cmd->builtin =  TRUE);
	if (!(ft_strncmp(cmd->args[0], "unset", 5)))
		return (cmd->builtin =  TRUE);
	if (!(ft_strncmp(cmd->args[0], "echo", 4)))
		return (cmd->builtin =  TRUE);
	return (cmd->builtin = FALSE);
}


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


int	is_redirect(char *str)
{
	if (!ft_strncmp(str, ">", -1) || !ft_strncmp(str, "<", -1))
		return (1);
	if (!ft_strncmp(str, ">>", -1) || !ft_strncmp(str, "<<", -1))
		return (1);
	return (0);
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
	if(*line != 0)
		create_node(line, index, first, relation);
}
