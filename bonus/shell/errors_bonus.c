/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 10:34:11 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/05/14 15:13:59 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_bonus.h"

/* int		check_next_relation(t_node *node)
{
} */
void	show_error(char *name, char *message, int status, int exit_from_shell_bonus)
{
	write(2, "Minishell_bonus: ", 12);
	write(2, name, ft_strlen(name));
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	g_data.exit_code = status;
	if (exit_from_shell_bonus)
	{
		clean_up();
		exit(g_data.exit_code);
	}
}
