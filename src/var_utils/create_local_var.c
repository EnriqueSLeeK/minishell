/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_local_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:53:43 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/15 14:14:37 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	create_local_var(char *key, char *value)
{
	if (key == 0)
		return (0);
	else
	{
		set_entry(g_data.local_vars, create_entry(key, value));
		return (0);
	}
}
