/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:32:27 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/17 23:26:47 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	create_env_var(char **arg, int flag);
static int	move_env_var(char **arg, int flag);

static int	create_env_var(char **arg, int flag)
{
	int	i;

	if (*arg == 0)
		return (flag);
	i = find_char(*arg, '=');
	if (check_varname(*arg) || i != 0)
	{
		(*arg)[i] = 0;
		set_entry(g_data.env_vars, create_entry((*arg),
				&((*arg)[i + 1])));
		(*arg)[i] = '=';
	}
	if (find_char(arg[1], '=') == -1)
		return (move_env_var(&(arg[1]), flag));
	else
		return (create_env_var(&(arg[1]), flag));
}

static int	move_env_var(char **arg, int flag)
{
	t_entry	**entry;

	if (*arg == 0)
		return (flag);
	if (check_varname(*arg))
	{
		entry = get_entry(g_data.local_vars, *arg);
		if (entry != 0)
		{
			set_entry(g_data.env_vars, *entry);
			*entry = 0;
		}
	}
	if (find_char(arg[1], '=') == -1)
		return (move_env_var(&(arg[1]), flag));
	else
		return (create_env_var(&(arg[1]), flag));
}

int	export(char	**args)
{
	if (find_char(args[1], '=') != -1)
		return (create_env_var(&(args[1]), 0));
	else
		return (move_env_var(&(args[1]), 0));
}
