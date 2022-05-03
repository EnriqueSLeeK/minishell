/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_list_util_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 21:20:56 by ensebast          #+#    #+#             */
/*   Updated: 2022/05/02 23:03:19 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	append_slash(char **file_list)
{
	char	*tmp;

	tmp = ft_strjoin(*file_list, "/");
	free(*file_list);
	*file_list = tmp;
}

int	open_dir(char *directory, DIR **dir)
{
	if (directory == 0)
		*dir = opendir(".");
	else
		*dir = opendir(directory);
	if (*dir == 0)
		return (1);
	return (0);
}

int	check_exp(char *file_name, char *exp)
{
	if (match_exp(exp, file_name))
		return (1);
	return (0);
}

void	is_dir(char *exp, int *flag)
{
	int	i;

	*flag = 0;
	i = ft_strlen(exp) - 1;
	while (i > -1)
	{
		if (exp[i] == '/')
			*flag = 1;
		if (*flag == 1 && exp[i] != '/')
			exp[i + 1] = 0;
		if (exp[i] != '/')
			break ;
		i -= 1;
	}
}

int	check_valid(struct dirent *file_entry, int dir_flag, char *exp)
{
	if (dir_flag == 1 && file_entry -> d_type == DT_DIR
		&& check_exp(file_entry -> d_name, exp))
		return (1);
	if (dir_flag == 0 && check_exp(file_entry -> d_name, exp))
		return (1);
	return (0);
}
