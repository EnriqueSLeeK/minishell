/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_regex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:32:04 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/06 18:32:18 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	find_diff(char c, char *exp);
static int	match_star(int c, char *regexp, char *text);
static int	match_symbol(char *regexp, char *text);

// Micro-regex start
int	match_exp(char *regexp, char *text)
{
	if (regexp == 0 || *regexp == 0)
		return (-1);
	if (match_symbol(regexp, text))
		return (1);
	return (0);
}

// Return a char
static int	find_diff(char c, char *exp)
{
	int	i;

	i = 0;
	while (exp[i])
	{
		if (c != exp[i])
			return (exp[i]);
		i += 1;
	}
	return (0);
}

//	Recursively call other functions
static int	match_symbol(char *regexp, char *text)
{
	if (*regexp == 0 && *text == 0)
		return (1);
	if (*regexp == '*')
		return (match_star(find_diff('*', regexp), regexp + 1, text));
	else if (*regexp == *text)
		return (match_symbol(regexp + 1, text + 1));
	return (0);
}

// Wildcard *
static int	match_star(int c, char *regexp, char *text)
{
	while (*text != 0 && *text != c)
		text += 1;
	return (match_symbol(regexp, text));
}
