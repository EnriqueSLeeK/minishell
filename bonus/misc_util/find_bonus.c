/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 15:25:35 by ensebast          #+#    #+#             */
/*   Updated: 2022/05/14 15:11:48 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_bonus.h"

int	find_char(char *str, char c)
{
	int	i;

	if (str == 0)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i += 1;
	}
	return (-1);
}
