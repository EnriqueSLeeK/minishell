/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_segment_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:46:08 by ensebast          #+#    #+#             */
/*   Updated: 2022/05/14 15:11:48 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_bonus.h"

void	skip_segment(char **line)
{
	int	i;
	int	flag;

	if (line == 0 || *line == 0)
		return ;
	i = find_char(*line, ' ');
	if (i != -1)
		*line += i + 1;
	while (**line)
	{
		if (**line != ' ')
			flag = 1;
		if (flag && **line == ' ')
			break ;
		*line += 1;
	}
}
