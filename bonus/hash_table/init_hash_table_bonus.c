/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hash_table_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:14:56 by ensebast          #+#    #+#             */
/*   Updated: 2022/05/14 15:11:48 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_bonus.h"

static int	find_equal(char *var_str)
{
	int	i;

	i = 0;
	while (var_str[i])
	{
		if (var_str[i] == '=')
			return (i);
		i += 1;
	}
	return (-1);
}

int	init_env_table(char *envp[])
{
	int	i;
	int	k;

	g_data.env_vars = ht_create();
	g_data.local_vars = ht_create();
	i = 0;
	while (envp[i])
	{
		k = find_equal(envp[i]);
		envp[i][k] = 0;
		set_entry(g_data.env_vars, create_entry(envp[i], &envp[i][k + 1]));
		envp[i][k] = '=';
		i += 1;
	}
	return (1);
}
