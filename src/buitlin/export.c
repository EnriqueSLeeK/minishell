/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:32:27 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/09 10:51:34 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	export(char	*key, char *value)
{
	t_entry	**entry; 

	if (value != 0 &&  *value != 0)
		return (set_entry(g_data.env_vars, create_entry(key, value)));
	else
	{
		entry = get_entry(g_data.local_vars, key);
		if (entry != 0)
		{
			set_entry(g_data.env_vars, *entry);
			*entry = 0;
			return (0);
		}
	}
	return (0);
}
