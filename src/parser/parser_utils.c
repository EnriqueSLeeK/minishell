/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 11:37:56 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/04/05 19:11:13 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	is_builtin(t_node *node)
{
	if (!ft_strncmp(node->args[0], "echo", 4))
		return (1);
	else if (!ft_strncmp(node->args[0], "cd", 2))
		return (1);
	else if (!ft_strncmp(node->args[0], "env", 3))
		return (1);
	else if (!ft_strncmp(node->args[0], "exit", 4))
		return (1);
	else if (!ft_strncmp(node->args[0], "export", 6))
		return (1);
	else if (!ft_strncmp(node->args[0], "pwd", 3))
		return (1);
	else if (!ft_strncmp(node->args[0], "unset", 5))
		return (1);
	else
		return (0);
}

int	is_file(t_node	*node)
{
	if (is_builtin(node))
		return (0);
	if (node->previous)
	{
		if (!ft_strncmp(node->previous->relation, "<<", 2))
			return (1);
		else if (!ft_strncmp(node->previous->relation, "<", 1))
		{
			if (!access(node->args[0], F_OK))
				return (1);
			else
				perror("Error");
		}
		else if (!ft_strncmp(node->previous->relation, ">", 1))
			return (1);
	}
	return (0);
}

void	set_type(t_node *node)

{
	node->is_builtin = 0;
	node->is_file = 0;
	if (is_builtin(node))
		node->is_builtin = 1;
	else if (is_file(node))
		node->is_file = 1;
}
