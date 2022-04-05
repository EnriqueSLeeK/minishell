/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:10:30 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/05 19:15:12 by ensebast         ###   ########.br       */
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
	if (sufix != 0)
}
