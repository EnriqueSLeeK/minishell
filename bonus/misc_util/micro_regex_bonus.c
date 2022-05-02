/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_regex_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:32:04 by ensebast          #+#    #+#             */
/*   Updated: 2022/05/02 20:17:23 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	match_symbol(char *regexp, char *text);

static char	*consume_extra(char *reg, char c)
{
	while (*reg == c && *(reg + 1) == c)
		reg += 1;
	return (reg);
}

static int	match_star(char *regexp, char *text)
{
	while (*text != 0)
	{
		if (match_symbol(regexp + 1, text))
			return (1);
		text += 1;
	}
	if (*text == 0 && *(regexp + 1) == 0)
		return (1);
	return (0);
}

// Match symbols
static int	match_symbol(char *regexp, char *text)
{
	if ((*regexp == 0 && *text == 0)
		|| (*regexp == 0 && *(regexp - 1) == '*'))
		return (1);
	if (*regexp == '*')
		return (match_star(consume_extra(regexp, '*'), text));
	if (*regexp && *text == *regexp)
		return (match_symbol(regexp + 1, text + 1));
	return (0);
}

// Micro-regex start
int	match_exp(char *regexp, char *text)
{
	if (regexp == 0 || *regexp == 0
		|| text == 0 || *text == 0)
		return (0);
	if (*text == '.' && *regexp != *text)
		return (0);
	else if (match_symbol(regexp, text))
		return (1);
	return (0);
}
