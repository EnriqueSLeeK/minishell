/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:15:48 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/04/20 11:28:48 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	get_second_quote(char *line, char quote)
{
	int	index;

	index = 0;
	while (line[index])
	{
		if (line[index] == quote)
			return (1);
		line++;
	}
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
			break ;
		}
		index++ ;
	}
	if (!quote)
		return (0);
	if (get_second_quote(&line[index], quote))
		return (0);
	else
	{
		show_error(M_QUOTES_ERROR, "", 2, 0);
		return (1);
	}
}
