/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:05:58 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/13 11:42:37 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*prompt(void)
{
	char	*line;

	line = readline("\e[1;34m minishell \e[01;34m>\e[00m ");
	if (line == 0)
	{
		clean_up();
		exit(1);
	}
	else
		add_history(line);
	return (line);
}
