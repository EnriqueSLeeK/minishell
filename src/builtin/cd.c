/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:44:07 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/17 23:19:49 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	update_pwd_var(void)
{
	char	*buff;
	char	*path;
	int		len;

	len = 15;
	buff = ft_calloc(sizeof(char), len);
	path = getcwd(buff, len);
	while (path == 0)
	{
		free(buff);
		len *= 2;
		buff = ft_calloc(sizeof(char), len);
		path = getcwd(buff, len);
	}
	set_entry(g_data.env_vars, create_entry("PWD", buff));
	free(buff);
}

int	change_dir(char	*path)
{
	char	*buff;

	if (path == 0)
		printf("cd: HOME not set\n");
	else if (path[0] == 0)
		return (0);
	else if (chdir(path) == 0)
	{
		update_pwd_var();
		return (0);
	}
	else
	{
		buff = ft_strjoin("cd: ", path);
		perror(buff);
		free(buff);
	}
	return (1);
}

int	cd(char **args)
{
	int		i;

	i = 1;
	if (args[i] == 0)
	{
		return (change_dir(get_value(g_data.env_vars, "HOME")));
	}
	else if (args[i + 1] == 0)
	{
		return (change_dir(args[i]));
	}
	else
	{
		printf("cd: Too many arguments\n");
		return (1);
	}
}
