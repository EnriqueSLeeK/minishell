/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_expansion_pre_split.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 00:59:00 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/11 18:34:12 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.c"

static int	search_expandable(char *line)
{
	int	mode;
	int	l;

	l = 0;
	mode = EXPAND;
	while (*line)
	{
		if (*line == '\'' && (mode & LOCK_E) != LOCK_E)
			mode ^= EXPAND;
		if (*line == '\"' && mode != IGNORE)
		{
			mode ^= EXPAND;
			mode ^= LOCK_E;
		}
		if (*line == '*' && (mode & EXPAND))
			break ;
		line += 1;
		l += 1;
	}
	return (l);
}

char	*get_pattern(char *line)
{
	char	*pattern;

	pattern = line;
	while (*line)
	{
		line += 1;
	}
	return (0);
}

int wild_expansion_pre_split(char **line)
{
	int		i;
	char	*pattern;

	i = search_expandable(*line);
	if (line[i] == 0 || line[i] != '*')
		return (0);
	wild_expansion_pre_split(line);
}
