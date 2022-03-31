/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:59:42 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/31 16:36:00 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	clean_up(void)
{
	free_table(&g_data.env_vars);
	free_table(&g_data.local_vars);
	free_operations();
	free_fds();
	rl_clear_history();
}

void	post_exec_clean(char *line, char **env)
{
	free_bmatrix(env);
	free_commands();
	free(line);
}
