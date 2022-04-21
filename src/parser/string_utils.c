/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:35:44 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/04/21 19:53:01 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*swap_char(char *line, char old_char, char new_char)
{
	int		index;
	char	quote;

	quote = 0;
	index = 0;
	while (line[index])
	{
		has_quote(&line[index], &quote);
		if (quote)
		{
			index++;
			while (quote && line[index])
			{
				if (line[index] == old_char)
					line[index] = new_char;
				index++;
				has_quote(&line[index], &quote);
			}
		}
		else if (line[index])
			index++;
	}
	return (line);
}

char	**swap_char_matrix(char **matrix)
{
	int	index;

	index = 0;
	while (matrix[index])
	{
		matrix[index] = swap_char(matrix[index], 1, ' ');
		index++;
	}
	return (matrix);
}
