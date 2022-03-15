/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:44:07 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/15 18:20:40 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	slash_check(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '/')
			return (1);
		i += 1;
	}
	return (0);
}

int	cd(char **args)
{
	int		i;
	char	*path;

	i = 0;
	if (ft_strncmp(args[i], "cd", ft_strlen(args[i])) == 0)
		i += 1;
	if (args[i] == 0)
	{
		path = get_value(g_data.env_vars, "HOME");
		if (chdir(path) == 0)
			set_entry(g_data.env_vars, create_entry("PWD", path));
	}
	else if (args[i] && slash_check(args[i]) && args[i + 1] == 0)
	{
		path = args[i];
		if (chdir(path) == 0)
			set_entry(g_data.env_vars, create_entry("PWD", path));
	}
	else
	{
		printf("Too many arguments\n");
		return (127);
	}
	return (0);
}
