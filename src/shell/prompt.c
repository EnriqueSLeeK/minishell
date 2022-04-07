/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:05:58 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/07 16:53:40 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*prompt(void)
{
	char	*line;

	rl_replace_line("", 1);
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
