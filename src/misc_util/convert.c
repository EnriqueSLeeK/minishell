/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:41:57 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/24 14:22:18 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*build_format(int i)
{
	char	*tmp;
	char	*line;

	line = 0;
	tmp = ft_strjoin((g_data.env_vars -> table[i]) -> key, "=");
	if (tmp != 0)
	{
		line = ft_strjoin(tmp, (g_data.env_vars -> table[i]) -> value);
		free(tmp);
	}
	return (line);
}

char	**convert_table_matrix(void)
{
	int		i;
	int		k;
	char	**buff;

	i = 0;
	k = 0;
	buff = ft_calloc((g_data.env_vars -> length) + 1, sizeof(char *));
	if (buff != 0)
	{
		while (i < g_data.env_vars -> capacity)
		{
			if (g_data.env_vars -> table[i] != 0)
			{
				buff[k] = build_format(i);
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
