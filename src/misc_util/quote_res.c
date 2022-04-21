/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_res.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:48:58 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/21 20:01:46 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// mode = 1 init struct t_parse_flag var
// mode = 0 update the flags in t_parse_flag
static void	init_or_update(t_parse_flag *flag, char c, int mode)
{
	if (mode)
	{
		flag -> sp_quote = 0;
		flag -> db_quote = 0;
		flag -> segment_flag = 0;
	}
	else
	{
		if (flag -> sp_quote == 2)
			flag -> sp_quote = 0;
		else if (flag -> db_quote == 2)
			flag -> db_quote = 0;
		if (c == '\'' && flag -> db_quote == 0)
			flag -> sp_quote += 1;
		else if (c == '\"' && flag -> sp_quote == 0)
			flag -> db_quote += 1;
	}
}

static int	calculate_len(char *line)
{
	int				size;
	t_parse_flag	flag;

	if (line == 0)
		return (-1);
	size = 0;
	init_or_update(&flag, 0, 1);
	while (*line)
	{
		init_or_update(&flag, *line, 0);
		if ((flag.sp_quote == 0 && flag.db_quote == 0)
			|| (flag.sp_quote == 1 && *line != '\'')
			|| (flag.db_quote == 1 && *line != '\"'))
			size += 1;
		line += 1;
	}
	return (size);
}

static void	solve_line(char *buff, char *line)
{
	t_parse_flag	flag;

	init_or_update(&flag, 0, 1);
	while (*line)
	{
		init_or_update(&flag, *line, 0);
		if ((flag.sp_quote == 0 && flag.db_quote == 0)
			|| (flag.sp_quote == 1 && *line != '\'')
			|| (flag.db_quote == 1 && *line != '\"'))
		{
			*buff = *line;
			buff += 1;
		}
		line += 1;
	}
}

static char	*treat_quotes(char *line)
{
	char	*buff;
	int		size;

	size = calculate_len(line);
	if (size != -1)
	{
		buff = ft_calloc(size + 1, sizeof(char));
		if (buff == 0)
			return (0);
		solve_line(buff, line);
	}
	else
		buff = 0;
	return (buff);
}

// Main function for this operation
char	*quote_resolution(char *line, int *flag)
{
	char	*buff;

	buff = 0;
	if (find_char(line, '\'') != -1 || find_char(line, '\"') != -1)
	{
		buff = treat_quotes(line);
		if (flag != 0)
			*flag = 0;
	}
	else
	{
		buff = ft_strdup(line);
		if (flag != 0)
			*flag = 1;
	}
	return (buff);
}
