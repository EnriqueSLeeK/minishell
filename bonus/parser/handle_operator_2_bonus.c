/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operator_2_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:02:17 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/05/14 15:11:48 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_bonus.h"

static t_node	*handle_and(t_node *node)
{
	if (g_data.exit_code == 0 && node->next)
		return (node->next);
	return (NULL);
}

static t_node	*handle_or(t_node *node)
{
	if (g_data.exit_code != 0 && node->next)
		return (node->next);
	return (NULL);
}

t_node	*get_next_node(t_node *node)
{
	if (node->relation)
	{
		if (!ft_strncmp(node->relation, "&&", 2))
			return (handle_and(node));
		else if (!ft_strncmp(node->relation, "||", 2))
			return (handle_or(node));
		else
			return (node->next);
	}
	return (node->next);
}
