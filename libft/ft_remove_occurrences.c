/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_occurrences.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:45:10 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/03/14 15:29:07 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_remove_occurrences(char **str, char c)
{
	int	i;
	int	len;
	int	j;

	i = 0;
	len = ft_strlen(*str);
	while (i < len)
	{
		if ((*str)[i] == c)
		{
			j = i;
			while (j < len)
			{
				(*str)[j] = (*str)[j + 1];
				j++;
			}
			i--;
			len--;
		}
		i++;
	}
}
