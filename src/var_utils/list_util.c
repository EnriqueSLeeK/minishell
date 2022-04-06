/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:25:14 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/06 18:41:09 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	check(char *file_name, char *exp)
{
	if (!(ft_strncmp(file_name, ".", 2) == 0
			|| ft_strncmp(file_name, "..", 3) == 0)
		&& match_exp(exp, file_name))
	{
		return (1);
	}
	return (0);
}

static int	count_file(char *exp)
{
	int				i;
	DIR				*dir;
	struct dirent	*file_entry;

	i = 0;
	dir = opendir(".");
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

static void	fill_list(char *exp, char **file_list)
{
	int				i;
	DIR				*dir;
	struct dirent	*file_entry;

	dir = opendir(".");
	if (dir == 0)
		return ;
	i = 0;
	file_entry = readdir(dir);
	while (file_entry)
	{
		if (check(file_entry -> d_name, exp))
		{
			file_list[i] = ft_strdup(file_entry -> d_name);
			i += 1;
		}
		file_entry = readdir(dir);
	}
	closedir(dir);
}

void	get_list_filter(char *exp, char ***file_list)
{
	int				quant;

	*file_list = 0;
	quant = count_file(exp);
	if (quant > 0)
		*file_list = ft_calloc(quant + 1, sizeof(char *));
	if (*file_list == 0)
		return ;
	fill_list(exp, *file_list);
}
