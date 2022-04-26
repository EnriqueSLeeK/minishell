/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:05:58 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/26 10:57:21 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	check_here_doc(char *line)
{
	t_parse_flag	flag;

	init_or_update(&flag, 0, 1);
	while (*line)
	{
		init_or_update(&flag, *line, 0);
		if (flag.sp_quote == 0 && flag.db_quote == 0 && *line == '<')
		{
			if (ft_strncmp("<<", line, 2) == 0)
				return (0);
		}
		line += 1;
	}
	return (1);
}

char	*prompt(void)
{
	char	*line;

	line = readline("\e[1;34m minishell \e[01;34m>\e[00m ");
	if (line == 0)
	{
		clean_up();
		exit(0);
	}
	else
	{
		if (*line != 0 && check_here_doc(line))
			add_history(line);
	}
	return (line);
}
