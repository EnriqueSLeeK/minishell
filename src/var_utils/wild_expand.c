/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 19:33:56 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/05 20:06:02 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	expand_wild(char ***parsed_line, int i, int k)
{
	int		count_files;
	char	*prefix;
	char	*sufix;

	parsed_line[i][k] = 0;
	prefix = parsed_line[i];
	sufix = parsed_line[i][k + 1];
}
