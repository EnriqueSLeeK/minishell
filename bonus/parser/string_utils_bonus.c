/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:35:44 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/05/14 15:13:18 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_bonus.h"

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
				has_quote(&line[index], &quote);
				index++;
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

char	*copy_string_trim(char **matrix, int j, int *is_active, char *quoute)
{
	int		i;
	int		desloc;
	char	*tmp;

	tmp = (char *) ft_calloc(ft_strlen(matrix[j]) + 1, sizeof(char));
	i = 0;
	desloc = 0;
	while (matrix[j][i + desloc])
	{
		if (check_quoute(matrix[j][i + desloc], is_active, quoute))
		{
			tmp[i] = matrix[j][i + desloc];
			i++;
		}
		else
			desloc++;
	}
	return (tmp);
}

void	trim_quotes(char **matrix)
{
	char	*tmp;
	int		j;
	int		is_active;
	char	quoute;

	j = 0;
	quoute = 0;
	is_active = FALSE;
	while (matrix[j])
	{
		tmp = copy_string_trim(matrix, j, &is_active, &quoute);
		free(matrix[j]);
		matrix[j] = tmp;
		j++;
	}
}

void	can_trim(t_node *node)
{
	if (node->previous)
	{
		if (!ft_strncmp(node->previous->relation, "<<", 2))
			return ;
		else
			trim_quotes(node->args);
	}
	else
		trim_quotes(node->args);
}
