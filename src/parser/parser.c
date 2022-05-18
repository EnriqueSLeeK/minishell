/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:53:01 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/05/18 11:02:38 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_node	*parse_cmd(char *line, char *relation)
{
	t_node	*node;
	char	*parsed_line;

	parsed_line = swap_char(line, ' ', 1);
	node = (t_node *)ft_calloc(sizeof(t_node), 1);
	node->args = ft_split(parsed_line, ' ');
	node->fd_out = 1;
	node->relation = relation;
	node->args = swap_char_matrix(node->args);
	free(line);
	return (node);
}

void	ft_parse(char *line)
{
	int		index;
	char	*relation;
	char	on_quote;

	index = 0;
	on_quote = 0;
	while (line[index] != '\0')
	{
		has_quote(&line[index], &on_quote);
		relation = is_in(g_data.operators, &line[index]);
		if (relation && !on_quote)
		{
			line = ft_create_cmd(line, index, relation);
			index = 0;
		}
		if (line[index])
			index++;
	}
	relation = NULL;
	if (*line != 0)
		ft_create_cmd(line, index, relation);
}

char	*is_in(char **operators, char *line)
{
	if (!ft_strncmp(operators[6], line, ft_strlen(operators[6])))
	{
		if (g_data.node)
		{
			if (g_data.node->relation && !g_data.node->args[0])
			{
				if ((!ft_strncmp(g_data.node->relation, "<", 1) \
				|| !ft_strncmp(g_data.node->relation, ">", 1)) \
				&& !g_data.node->next)
					return (operators[6]);
				else
					return (0);
			}
		}
		else
			return (0);
	}
	while (*operators)
	{
		if (!ft_strncmp(*operators, line, ft_strlen(*operators)))
			return (*operators);
		operators++;
	}
	return (0);
}

void	add_new_node(t_node *node)
{
	t_node	*last;

	last = g_data.node;
	if (last != NULL)
	{
		while (last->next)
			last = last->next;
		last->next = node;
		node->previous = last;
	}
	else
		g_data.node = node;
}

char	*ft_create_cmd(char *line, int index, char *relation)
{
	t_node	*node;

	while (*line == ' ' || *line == '\t')
	{
		index--;
		line++;
	}
	line[index] = '\0';
	if (relation)
		if (!ft_strncmp(relation, "<<", 2) || !ft_strncmp(relation, ">>", 2))
			index++;
	line[index] = '\0';
	node = parse_cmd(ft_strdup(line), relation);
	add_new_node(node);
	if (node && node->args[0])
		set_type(node);
	if (!node->is_builtin && !node->is_file)
		search_bin(node->args);
	return (line += index + 1);
}
