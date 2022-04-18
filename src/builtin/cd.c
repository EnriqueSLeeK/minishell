/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:44:07 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/18 15:27:13 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*get_dir(void);
static int	change_dir(char	*path);
static int	change_preset_dir(char *var_name);
static void	update_pwd_var(char *var, char *path);

static char	*get_dir(void)
{
	char	*buff;
	char	*path;
	int		len;

	len = 15;
	buff = ft_calloc(sizeof(char), len);
	if (buff != 0)
		path = getcwd(buff, len);
	else
		return (0);
	while (path == 0)
	{
		free(buff);
		len *= 2;
		buff = ft_calloc(sizeof(char), len);
		if (buff != 0)
			path = getcwd(buff, len);
		else
			return (0);
	}
	return (buff);
}

static int	change_preset_dir(char *var_name)
{
	char	*path;
	char	*buff;
	char	*tmp;

	tmp = 0;
	buff = 0;
	path = get_value(g_data.env_vars, var_name);
	if (path == 0 || *path == 0)
	{
		tmp = ft_strjoin("cd: ", var_name);
		if (tmp != 0)
		{
			buff = ft_strjoin(tmp, " not set\n");
			if (buff != 0)
				write(2, buff, ft_strlen(buff));
		}
		free(tmp);
		free(buff);
		return (1);
	}
	return (change_dir(path));
}

static void	update_pwd_var(char *var, char *path)
{
	set_entry(g_data.env_vars, create_entry(var, path));
}

static int	change_dir(char	*path)
{
	char	*buff;
	char	*old_dir;

	old_dir = get_dir();
	if (old_dir == 0)
		return (1);
	if (chdir(path) == 0)
	{
		update_pwd_var("OLDPWD", old_dir);
		update_pwd_var("PWD", path);
		free(old_dir);
		return (0);
	}
	else
	{
		buff = ft_strjoin("cd: ", path);
		perror(buff);
		free(buff);
	}
	free(old_dir);
	return (1);
}

int	cd(char **args)
{
	int		i;

	i = 1;
	if (args[i] == 0)
	{
		return (change_preset_dir("HOME"));
	}
	else if (args[i + 1] == 0 && (ft_strncmp(args[i], "-", 2) == 0))
	{
		return (change_preset_dir("OLDPWD"));
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
