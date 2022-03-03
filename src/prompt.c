/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:05:58 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/02 23:43:26 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*prompt(void)
{
	char	*line;

	line = readline("\e[32m minishell \e[01;32m>\e[00m ");
	if (line == 0)
	{
		rl_clear_history();
		exit(1);
	}
	else
		add_history(line);
	return (line);
}
