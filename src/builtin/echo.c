/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:39:11 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/18 19:53:16 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	check_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i += 1;
	}
	return (1);
}

static void	find_flag(char **args, int *index, int *flag)
{
	int	aux;

	*index = 1;
	*flag = 0;
	aux = 0;
	while (args[*index] && args[*index][0] == '-'
		&& args[*index][1] != 0)
	{
		aux = check_line(&(args[*index][1]));
		*flag |= aux;
		if (aux == 0)
			break ;
		*index += 1;
	}
}

static void	print_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1] != 0)
			write(1, " ", 1);
		i += 1;
	}
}

int	echo(char **args)
{
	int	flag;
	int	index;

	if (args != 0 && *args != 0)
	{
		find_flag(args, &index, &flag);
		print_args(&(args[index]));
		if (!(flag))
			write(1, "\n", 1);
	}
	return (0);
}
