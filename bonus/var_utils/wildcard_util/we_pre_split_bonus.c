/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_pre_split_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 12:20:30 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/19 17:22:49 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*make_line(char *pattern);
void	get_pattern(char *line, int *i);
void	prepare_line(char **line, int i);
char	*translate_line(char *line, int i);
void	joining(char **dest, char *file, char *next);

static void	check(int *mode, char c)
{
	if (c == '<')
		*mode |= OP_ARG;
	else if (c == '\'' && (*mode & LOCK_E) != LOCK_E)
		*mode ^= EXPAND;
	else if (c == '\"' && *mode != IGNORE)
	{
		*mode ^= EXPAND;
		*mode ^= LOCK_E;
	}
}

static int	search_expandable(char *line)
{
	int	mode;
	int	l;

	l = 0;
	mode = EXPAND;
	while (*line)
	{
		check(&mode, *line);
		if (mode & OP_ARG)
		{
			if (*(line + 1) == '<')
				skip_segment(&line);
			mode ^= OP_ARG;
		}
		if (*line == '*' && (mode & EXPAND) && (mode ^ OP_ARG))
			break ;
		line += 1;
		l += 1;
	}
	return (l);
}

void	we_pre_split(char **line, int index)
{
	int		i;
	int		segment_start;

	i = search_expandable((*line + index)) + index;
	if ((*line)[i] == 0 || (*line)[i] != '*')
		return ;
	segment_start = i;
	get_pattern((*line + segment_start), &segment_start);
	prepare_line(line, segment_start);
	we_pre_split(line, i + 1);
}
