/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:59:42 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/04 17:00:17 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	clean_up(void)
{
	unlink("/tmp/tmp_f");
	free_table(&g_data.env_vars);
	free_table(&g_data.local_vars);
	free_operations();
	free_fds();
	rl_clear_history();
}

void	post_exec_clean(char *line)
{
	free_bmatrix(g_data.envp);
	free_commands();
	free(line);
}
