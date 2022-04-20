/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 13:44:03 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/19 21:36:31 by ensebast         ###   ########.br       */
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
