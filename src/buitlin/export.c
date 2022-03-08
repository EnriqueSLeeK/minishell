/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:32:27 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/08 16:50:44 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	export(char	*key, char *value)
{
	remove_entry(g_data.local_vars, key);
	return (set_entry(g_data.env_vars, create_entry(key, value)));
}
