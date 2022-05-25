/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 11:37:56 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/05/25 11:32:41 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_bonus.h"

int	is_builtin(t_node *node)
{
	if (!ft_strncmp(node->args[0], "echo", ft_strlen(node->args[0])))
		return (1);
	else if (!ft_strncmp(node->args[0], "cd", ft_strlen(node->args[0])))
		return (1);
	else if (!ft_strncmp(node->args[0], "env", ft_strlen(node->args[0])))
		return (1);
	else if (!ft_strncmp(node->args[0], "exit", ft_strlen(node->args[0])))
		return (1);
	else if (!ft_strncmp(node->args[0], "export", ft_strlen(node->args[0])))
		return (1);
	else if (!ft_strncmp(node->args[0], "pwd", ft_strlen(node->args[0])))
		return (1);
	else if (!ft_strncmp(node->args[0], "unset", ft_strlen(node->args[0])))
		return (1);
	else
		return (0);
}

int	is_file(t_node	*node)
{
	if (node->previous)
	{
		if (!ft_strncmp(node->previous->relation, "<<", 2))
			return (1);
		else if (!ft_strncmp(node->previous->relation, "<", 1))
		{
			if (!access(node->args[0], F_OK))
				return (1);
			else
			{
				perror(node->args[0]);
				return (1);
			}
		}
		else if (!ft_strncmp(node->previous->relation, ">", 1))
			return (1);
	}
	return (0);
}

void	set_type(t_node *node)

{
	int	index;

	index = 0;
	while (node->args[0][index] == '/' && node->args[0])
		index++;
	if (index == ft_strlen(node->args[0]))
	{
		node->is_file = 1;
		printf("Minishell: %s: Is a directory\n", node->args[0]);
		return ;
	}
	if (is_builtin(node))
		node->is_builtin = 1;
	else if (is_file(node))
	{
		node->is_builtin = 0;
		node->is_file = 1;
	}
}

/* 		if (!ft_strncmp(node->relation, "|", ft_strlen(node->relation)))
			show_error(M_ERROR_SYNTAX, "|", 2, 0);
		else */
int	check_next_relation(t_node *node)
{
	if (node->relation && (!ft_strncmp(node->relation, "|", \
	ft_strlen(node->relation)) && !node->args[0]))
	{
		show_error(M_ERROR_SYNTAX, node->relation, 2, 0);
		return (1);
	}
	if (node->relation && (!node->next || !node->next->args \
		|| !node->next->args[0]))
	{
		show_error(M_ERROR_SYNTAX, "'newline'", 2, 0);
		return (1);
	}
	if ((node->sub_line && node->previous) && !node->previous->relation)
	{
		show_error(M_ERROR_SYNTAX, "( or )", 2, 0);
		return (1);
	}
	if ((node->sub_line && node->next) && !node->relation)
	{
		show_error(M_ERROR_SYNTAX, node->next->args[0], 2, 0);
		return (1);
	}
	return (0);
}

char	*get_full_instruction(t_node *node)
{
	char	*buffer;
	int		index;
	char	*tmp;

	index = 0;
	buffer = ft_strdup("");
	while (node->args[index])
	{
		tmp = ft_strdup(buffer);
		free(buffer);
		buffer = ft_strjoin(tmp, node->args[index]);
		free(tmp);
		index++;
	}
	return (buffer);
}
