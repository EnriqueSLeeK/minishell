/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:32:35 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/07 15:41:23 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// Hashing function: FNV-1a
unsigned long long int	hash(const char *data_byte)
{
	unsigned long long int	key;
	int						i;

	i = 0;
	key = FNV_OFFSET;
	while (data_byte[i])
	{
		key ^= (unsigned long long int)(unsigned char)data_byte[i];
		key *= FNV_PRIME;
		i += 1;
	}
	return (key);
}
