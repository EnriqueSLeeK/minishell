/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 13:44:03 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/07 16:30:11 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	action(int *f, char **parsed, int flag)
{
	int		k;

	k = find_char(parsed[0], '$');
	if (k != -1 && parsed[0][k] == '$')
	{
		expand_mix(&parsed[0], k, flag);
		*f = flag;
	}
}

// This function will expand variables
// If the wildcard '*' is found, expand the var first(if any)
// and then match the pattern found
void	var_expansion(char ***parsed_line, int flag)
{
	int		i;
	int		f;
	char	**parsed;

	i = 0;
	f = 0;
	if (parsed_line == 0 || (*parsed_line) == 0)
		return ;
	parsed = *parsed_line;
	while (parsed[i])
	{
		action(&f, &(parsed[i]), flag);
		if (find_char(parsed[0], '*') != -1)
		{
			expand_wild(parsed_line, i);
			parsed = *parsed_line;
		}
		if (f == EXPAND_ONE)
			break ;
		i += 1;
	}
}
