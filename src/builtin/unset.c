/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:38:54 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/18 20:12:34 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	unset(char **key)
{
	if (key == 0 || *key == 0 || **key == 0)
		return (0);
	remove_entry(g_data.local_vars, *key);
	remove_entry(g_data.env_vars, *key);
	return (unset((key + 1)));
}
