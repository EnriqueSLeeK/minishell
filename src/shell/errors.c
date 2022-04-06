/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 10:34:11 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/04/06 11:24:38 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/* int		check_next_relation(t_node *node)
{
} */
void	show_error(char *name, char *message, int status, int exit_from_shell)
{
	write(2, "Minishell: ", 12);
	write(2, name, ft_strlen(name));
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	g_data.exit_code = status;
	if (exit_from_shell)
	{
		clean_up();
		exit(g_data.exit_code);
	}
}
