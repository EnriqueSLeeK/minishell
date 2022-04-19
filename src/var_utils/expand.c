/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:29:43 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/19 17:22:06 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*prepare(char *parsed_line, char *var_name, int k);
char	*contructor(char *buff, char *tmp);
char	*seach_var(char *var_name);

void	check(int *mode, char c)
{
	if (c == '<' && (*mode ^ OP_ARG))
		*mode |= OP_ARG;
	else if (c == '\'' && (*mode & LOCK_E) != LOCK_E)
		*mode ^= EXPAND;
	else if (c == '\"' && *mode != IGNORE)
	{
		*mode ^= IGNORE;
		*mode ^= LOCK_E;
	}
}

int	search_expandable_var(char *line)
{
	int	mode;
	int	l;

	mode = EXPAND;
	l = 0;
	while (*line)
	{
		check(&mode, *line);
		if (mode & OP_ARG)
		{
			if (*(line + 1) == '<')
				skip_segment(&line);
			mode ^= OP_ARG;
		}
		if (*line == '$' && (mode & EXPAND))
			break ;
		line += 1;
		l += 1;
	}
	return (l);
}

// Expansion when mixed with string
void	expand_mix(char **parsed_line, int flag)
{
	int		k;
	char	*line;
	char	*var_name;

	k = search_expandable_var(*parsed_line);
	if (k == -1 || (*parsed_line)[k] != '$')
		return ;
	var_name = &((*parsed_line)[k + 1]);
	(*parsed_line)[k] = 0;
	line = prepare(*parsed_line, var_name, k);
	free(*parsed_line);
	*parsed_line = line;
	if (flag != EXPAND_ONE)
		expand_mix(parsed_line, flag);
}
