/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:53:01 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/04/06 10:44:25 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_parse(char *line)
{
	int		index;
	char	*relation;

	index = 0;
	while (line[index] != '\0')
	{
		relation = is_in(g_data.operators, &line[index]);
		if (relation)
		{
			line = ft_create_cmd(line, index, relation);
			index = 0;
		}
		index++;
	}
	relation = NULL;
	if (*line != 0)
		ft_create_cmd(line, index, relation);
}

char	*is_in(char **operators, char *line)
{
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

	line[index] = '\0';
	if (relation)
		if (!ft_strncmp(relation, "<<", 2) || !ft_strncmp(relation, ">>", 2))
			index += 1;
	line[index] = '\0';
	node = (t_node *)malloc(sizeof(t_node));
	node->args = ft_split(line, ' ');
	node->relation = relation;
	node->next = NULL;
	node->previous = NULL;
	node->fd_in = 0;
	node->fd_out = 0;
	search_bin(node->args);
	add_new_node(node);
	if(node->args[0])
		set_type(node);
	if (node->is_file)
		relation = NULL;
	return (line += index + 1);
}

void	link_relation(void)
{
	t_node	*node;

	node = g_data.node;
	while (node)
	{
		if (node->relation && !node->is_file)
		{
			if (!ft_strncmp(node->relation, "|", 1))
				handle_pipe(node);
			else if (!ft_strncmp(node->relation, "<<", 2))
				handle_here_doc(node);
			else if (!ft_strncmp(node->relation, ">>", 2))
				handle_red_output(node);
			else if (!ft_strncmp(node->relation, ">", 1))
				handle_red_output(node);
			else if (!ft_strncmp(node->relation, "<", 1))
				handle_red_intput(node);
		}
		node = node->next;
	}
}
