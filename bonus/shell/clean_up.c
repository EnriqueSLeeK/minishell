/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:59:42 by ensebast          #+#    #+#             */
/*   Updated: 2022/05/05 21:50:04 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	clean_up(void)
{
	unlink("/tmp/tmp_f");
	free_table(&g_data.env_vars);
	free_table(&g_data.local_vars);
	free_operations();
	free_commands();
	free_fds();
	rl_clear_history();
}

void	child_clean_up(char **envp, int exit_code)
{
	if (envp != 0)
		free_bmatrix(envp);
	free_table(&g_data.env_vars);
	free_table(&g_data.local_vars);
	free_operations();
	free_commands();
	free_fds();
	rl_clear_history();
	exit(exit_code);
}

void	post_exec_clean(char *line)
{
	g_data.status = CONTINUE;
	free_bmatrix(g_data.envp);
	free_commands();
	free(line);
	unlink("/tmp/tmp_f");
}
