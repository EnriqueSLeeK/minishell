/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_local_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:53:43 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/18 16:50:26 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	check_assign(char **arg);
static int	create_local_var(char **arg, int flag);

// Funtion return value meaning
// -1 => Success valid variable name
// if invalid return the index
int	check_varname(char *var_name)
{
	int	i;

	if (var_name == 0)
		return (0);
	i = 0;
	if (ft_isalpha(var_name[i]) || var_name[i] == '_')
	{
		i += 1;
		while (var_name[i] && var_name[i] != '=')
		{
			if (!(ft_isalpha(var_name[i]) || ft_isdigit(var_name[i])
					|| var_name[i] == '_'))
				return (i);
			i += 1;
		}
	}
	else
		return (i);
	return (-1);
}

// Check if all assignment are valid
static int	check_assign(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!(check_varname(arg[i]) == -1) || (find_char(arg[i], '=') < 1))
			return (0);
		i += 1;
	}
	return (1);
}

// Local var creation recursively
static int	create_local_var(char **arg, int flag)
{
	int	i;

	if (*arg == 0)
		return (flag);
	i = find_char(*arg, '=');
	if (i > 0 && check_varname(*arg) == -1)
	{
		(*arg)[i] = 0;
		set_entry(g_data.local_vars, create_entry(*arg, &((*arg)[i + 1])));
		(*arg)[i] = '=';
	}
	return (create_local_var(&(arg[i + 1]), flag));
}

// Main function for local_var creation
int	local_var(char **arg)
{
	if (check_assign(arg))
		return (create_local_var(arg, 0));
	return (127);
}
