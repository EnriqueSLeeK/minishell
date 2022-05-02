/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_list_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:25:14 by ensebast          #+#    #+#             */
/*   Updated: 2022/05/02 20:44:40 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	check(char *file_name, char *exp)
{
	if (match_exp(exp, file_name))
		return (1);
	return (0);
}

static int	count_file(char *directory, char *exp)
{
	int				i;
	DIR				*dir;
	struct dirent	*file_entry;

	i = 0;
	if (directory == 0)
		dir = opendir(".");
	else
		dir = opendir(directory);
	if (dir == 0)
		return (-1);
	file_entry = readdir(dir);
	while (file_entry)
	{
		if (check(file_entry -> d_name, exp))
			i += 1;
		file_entry = readdir(dir);
	}
	closedir(dir);
	return (i);
}

static void	fill_list(char *directory, char *exp, char **file_list)
{
	int				i;
	DIR				*dir;
	struct dirent	*file_entry;

	if (directory == 0)
		dir = opendir(".");
	else
		dir = opendir(directory);
	if (dir == 0)
		return ;
	i = 0;
	file_entry = readdir(dir);
	while (file_entry)
	{
		if (check(file_entry -> d_name, exp))
		{
			if (directory == 0)
				file_list[i] = ft_strdup(file_entry -> d_name);
			else
				file_list[i] = ft_strjoin(directory, file_entry -> d_name);
			i += 1;
		}
		file_entry = readdir(dir);
	}
	closedir(dir);
}

char	*separate_and_get_dir(char **exp)
{
	char	*dir;
	char	c;
	int		i;

	i = ft_strlen(*exp) - 1;
	while (i > -1)
	{
		if ((*exp)[i] == '/')
			break ;
		i -= 1;
	}
	if (i > -1)
	{
		c = (*exp)[i + 1];
		(*exp)[i + 1] = 0;
		dir = ft_strdup(*exp);
		(*exp)[i + 1] = c;
		*exp = &((*exp)[i + 1]);
		return (dir);
	}
	return (0);
}

void	get_list_filter(char *exp, char ***file_list)
{
	int				quant;
	char			*directory;

	*file_list = 0;
	directory = separate_and_get_dir(&exp);
	quant = count_file(directory, exp);
	if (quant > 0)
		*file_list = ft_calloc(quant + 1, sizeof(char *));
	if (*file_list == 0)
		return ;
	fill_list(directory, exp, *file_list);
	free(directory);
}
