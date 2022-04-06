/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:22:46 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/06 18:32:41 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	list_size(char **list)
{
	int	i;

	i = 0;
	while (list[i])
		i += 1;
	return (i);
}

void	move_pointer(char **dest, char **src, int *b_i)
{
	while (*src)
	{
		dest[*b_i] = *src;
		*b_i += 1;
		src += 1;
	}
}

char	**list_join(char **list_one, char **list_two, int i)
{
	int		b_i;
	char	**buff;

	buff = ft_calloc(list_size(list_one) + list_size(list_two) + 1,
			sizeof(char *));
	if (buff == 0)
		return (0);
	b_i = 0;
	while (*list_one)
	{
		if (b_i == i)
			move_pointer(buff, list_two, &b_i);
		else
		{
			buff[b_i] = *list_one;
			b_i += 1;
		}
		list_one += 1;
	}
	return (buff);
}

// Principal
void	expand_wild(char ***parsed_line, int i)
{
	char	**file_list;
	char	**tmp;

	if (parsed_line == 0
		|| *parsed_line == 0
		|| **parsed_line == 0)
		return ;
	get_list_filter((*parsed_line)[i], &file_list);
	tmp = list_join(*parsed_line, file_list, i);
	free((*parsed_line)[i]);
	free(*parsed_line);
	*parsed_line = tmp;
	free(file_list);
}
