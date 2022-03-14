/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 13:44:56 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/13 14:42:04 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// Check if there is a path
static int	contain_slash(char *bin)
{
	int	i;

	i = 0;
	while (i < ft_strlen(bin))
	{
		if (bin[i] == '/')
			return (1);
	}
	return (0);
}

// Free bidimensional array of type char **
static char	**free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i += 1;
	}
	free(matrix);
}

static char	*prepare_bin_path(char *path, char *bin, char **bin_path)
{
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	if (tmp == 0)
		printf("Slash append failed\n");
	*bin_path = ft_strjoin(tmp, bin);
	if (*bin_path == 0)
		printf("Failed to prepare the path");
	free(tmp);
}

// Using the path var stored in the hashmap search
// the bin
static char	*search(char *bin)
{
	int		i;
	char	**path;
	char	*bin_path;

	i = 0;
	path = ft_split(get_value(g_data.env_vars, "PATH"), ':');
	if (path == 0)
		printf("ft_split failure\n");
	else
	{
		while (path[i])
		{
			prepare_bin_path(path[i], bin, &bin_path);
			if (bin_path == 0)
				printf("ft_strjoin failure\n");
			if (access(bin_path, X_OK) == 0)
			{
				free_matrix(path);
				return (bin_path);
			}
			i += 1;
		}
	}
	free_matrix(path);
	return (ft_strdup(bin));
}

int	search_bin(char *bin, t_cmd *cmd)
{
	if (contain_slash(bin))
		cmd -> bin_with_path = ft_strdup(bin);
	else
		cmd -> bin_with_path = search(bin);
	return (1);
}