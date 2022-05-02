/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 13:44:03 by ensebast          #+#    #+#             */
/*   Updated: 2022/05/02 20:43:40 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// This function will expand variables
void	var_expansion_list(char **line, int flag)
{
	while (*line)
	{
		if (find_char(*line, '$') == -1)
			expand_mix(line, flag);
		line += 1;
	}
}

void	var_expansion_line(char **line, int flag)
{
	expand_mix(line, flag);
}

void	star_expansion(t_node *node)
{
	int		i;

	if (node == 0)
		return ;
	i = 0;
	while (node -> args[i])
	{
		if (find_char(node -> args[i], '*') != -1)
			expand_wild(&(node -> args), i);
		i += 1;
	}
	star_expansion(node -> next);
}
