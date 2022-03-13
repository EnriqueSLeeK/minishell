/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstrim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:22:12 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/03/08 15:28:36 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstrim(char const *str, char spliter)
{
	size_t	i;
	size_t	begin;

	if(!s)
		return (NULL);
	i = 0;
	while (*(str + i) == spliter)
		i++;
	begin = i;
	i = ft_strlen(str) - 1;
	if(begin != )
}