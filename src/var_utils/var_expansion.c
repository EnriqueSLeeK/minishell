/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 13:44:03 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/12 14:17:17 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// Search for the value then expand, if not found
// put a empty string
static void	expand(char **parsed_line)
{
	char	*buff;

	buff = get_value(g_data.env_vars, *parsed_line);
	if (buff == 0)
		buff = get_value(g_data.local_vars, *parsed_line);
	free(*parsed_line);
	if (buff == 0)
		*parsed_line = ft_calloc(sizeof(char), 1);
	else
		*parsed_line = buff;
}

void	var_expansion(char **parsed_line)
{
	int		i;

	i = 0;
	while (parsed_line[i])
	{
		if (ft_strncmp(parsed_line[i], "||", 3) == 0
			|| ft_strncmp(parsed_line[i], "&&", 3) == 0)
			break ;
		else if (parsed_line[i][0] == '$')
		{
			if (parsed_line[i][1] == 0)
			{
				free(parsed_line[i]);
				parsed_line[i] = ft_calloc(sizeof(char), 1);
			}
			else
			{
				expand(&parsed_line[i]);
				break ;
			}
		}
		i += 1;
	}
}
