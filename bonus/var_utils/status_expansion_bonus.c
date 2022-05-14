/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_expansion_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:50:38 by ensebast          #+#    #+#             */
/*   Updated: 2022/05/14 15:14:40 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_bonus.h"

// Index for the int_str
static int	index_calc(int aux)
{
	int	i;

	i = 1;
	while (aux > 9)
	{
		i += 1;
		aux /= 10;
	}
	return (i - 1);
}

// Convert int to string
static void	int_str(char *buff)
{
	int	aux;

	aux = g_data.exit_code;
	while (aux > 0)
	{
		buff[index_calc(aux)] = '0' + (aux % 10);
		aux /= 10;
	}
}

// Status code expansion
char	*status_code(void)
{
	char	*buff;

	buff = ft_calloc(index_calc(g_data.exit_code) + 2, sizeof(char));
	if (g_data.exit_code == 0)
		buff[0] = g_data.exit_code + '0';
	else
		int_str(buff);
	return (buff);
}
