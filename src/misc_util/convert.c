/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:41:57 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/31 17:06:45 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*build_format(t_hash_table *tab, int i)
{
	char	*tmp;
	char	*line;

	line = 0;
	tmp = ft_strjoin((tab->table[i])->key, "=");
	if (tmp != 0)
	{
		line = ft_strjoin(tmp, (tab->table[i])->value);
		free(tmp);
	}
	return (line);
}

char	**convert_table_matrix(t_hash_table *tab)
{
	int		i;
	int		k;
	char	**buff;

	i = 0;
	k = 0;
	buff = ft_calloc((tab -> length) + 1, sizeof(char *));
	if (buff != 0)
	{
		while (i < tab -> capacity)
		{
			if (tab -> table[i] != 0)
			{
				buff[k] = build_format(tab, i);
				if (buff[k] != 0)
					k += 1;
				else
					printf("Something is wrong\n");
			}
			i += 1;
		}
		return (buff);
	}
	return (0);
}
