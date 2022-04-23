/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:15:48 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/04/23 10:56:36 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	get_second_quote(char *line, char quote, int *last_index)
{
	int	index;

	index = 0;
	while (line[index])
	{
		if (line[index] == quote)
		{
			*last_index += index;
			return (1);
		}
		index++;
	}
	return (0);
}

static int	is_quoute(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

int	check_quotes(char *line)
{
	int		index;
	char	quote;

	index = 0;
	quote = 0;
	while (line[index])
	{
		if (line[index] == '\'' || line[index] == '\"')
		{
			quote = line[index];
			index++;
			if(get_second_quote(&line[index], quote, &index))
				quote = FALSE;
		}
		index++ ;
	}
	if (!quote)
		return (0);
	else
	{
		show_error(M_QUOTES_ERROR, "", 2, 0);
		return (1);
	}
}

void	has_quote(char *line, char *quote)
{
	if (*line == '\'' || *line == '"')
	{
		if (!*quote)
			*quote = *line;
		else if (*quote && *line == *quote)
			*quote = FALSE;
	}
}

int	check_quoute(char c, int *is_active, char *quoute)
{
	if (!*is_active && is_quoute(c) && c != *quoute)
	{
		*quoute = c;
		*is_active = TRUE;
		return (0);
	}
	if (*is_active == TRUE && c == *quoute)
	{
		*quoute = 0;
		*is_active = FALSE;
		return (0);
	}
	return (1);
}

void	can_trim(t_node *node)
{
	if(node->previous)
	{
		if(!ft_strncmp(node->previous->relation, "<<", 2))
			return ;
		else
			trim_quotes(node->args);
	}
	else
		trim_quotes(node->args);
}
