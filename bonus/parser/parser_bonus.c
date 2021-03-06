/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:53:01 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/05/25 18:52:34 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_bonus.h"

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
	char	on_quote;
	int		last_total_nodes;

	index = 0;
	on_quote = 0;
	last_total_nodes = g_data.total_nodes;
	while (line[index] != '\0')
	{
		has_quote(&line[index], &on_quote);
		line = check_relation(line, &index, on_quote);
		if (g_data.total_nodes > last_total_nodes)
		{
			last_total_nodes = g_data.total_nodes;
			continue ;
		}
		if (line[index])
			index++;
	}
	if (*line != 0)
		ft_create_cmd(line, index, NULL);
}

char	*is_in(char **operators, char *line)
{
	if (!ft_strncmp(operators[8], line, ft_strlen(operators[8])))
	{
		if (g_data.node)
		{
			if (g_data.node->relation && !g_data.node->args[0])
			{
				if ((!ft_strncmp(g_data.node->relation, "<", 1) \
				|| !ft_strncmp(g_data.node->relation, ">", 1)) \
				&& !g_data.node->next)
					return (operators[8]);
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
		if (!ft_strncmp(relation, "<<", 2) || !ft_strncmp(relation, ">>", 2) \
			|| !ft_strncmp(relation, "&&", 2) || !ft_strncmp(relation, "||", 2))
			index += 1;
	line[index] = '\0';
	node = parse_cmd(ft_strdup(line), relation);
	add_new_node(node);
	if (node->args[0])
		set_type(node);
	if (!node->is_builtin && !node->is_file)
		search_bin(node->args);
	g_data.total_nodes += 1;
	return (line += index + 1);
}
