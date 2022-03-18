/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:40:28 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/17 23:21:39 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	print_pwd(void)
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
	printf("%s\n", path);
	free(buff);
}

int	pwd(void)
{
	print_pwd();
	return (0);
}
