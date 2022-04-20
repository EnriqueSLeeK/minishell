/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_pre_util_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:49:27 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/13 18:05:36 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	get_pattern(char *line, int *i)
{
	while (*i > -1 && *line
		&& *line != ' ')
	{
		line -= 1;
		*i -= 1;
	}
	if (*i < 0)
	{
		line -= *i;
		*i -= *i;
		return ;
	}
	if (*line != '*')
		*i += 1;
}

void	joining(char **dest, char *file, char *next)
{
	char	*tmp;
	char	*aux;

	if (next == 0)
		tmp = ft_strdup(file);
	else
		tmp = ft_strjoin(file, " ");
	aux = *dest;
	*dest = ft_strjoin(aux, tmp);
	free(tmp);
	free(aux);
}

char	*make_line(char *pattern)
{
	char	**tmp;
	char	*line;
	int		i;

	get_list_filter(pattern, &tmp);
	if (tmp != 0)
	{
		line = strdup("");
		i = 0;
		while (tmp[i])
		{
			joining(&line, tmp[i], tmp[i + 1]);
			i += 1;
		}
		free_bmatrix(tmp);
		return (line);
	}
	return (ft_strdup(pattern));
}

char	*translate_line(char *line, int i)
{
	int		offset;
	char	*tmp;
	char	*buff;
	char	*res;

	tmp = 0;
	offset = find_char(&(line[i]), ' ');
	if (offset != -1)
	{
		tmp = ft_strdup(&(line[i + offset]));
		line[i + offset] = 0;
	}
	buff = make_line(&(line[i]));
	if (tmp != 0)
		res = ft_strjoin(buff, tmp);
	else
		res = ft_strdup(buff);
	free(tmp);
	free(buff);
	return (res);
}

void	prepare_line(char **line, int i)
{
	char	*prefix;
	char	*buff;
	char	c;

	c = (*line)[i];
	(*line)[i] = 0;
	prefix = ft_strdup(*line);
	(*line)[i] = c;
	buff = translate_line(*line, i);
	free(*line);
	*line = ft_strjoin(prefix, buff);
	free(buff);
	free(prefix);
}
