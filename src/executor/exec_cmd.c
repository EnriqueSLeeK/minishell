/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 10:26:57 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/03/31 16:23:56 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	exec_extern_cmd(t_node *node)
{
	g_data.exit_code = execve(node->args[0], node->args, g_data.envp);
	exit(15);
}

void	execute_cmd(t_node *node)
{
	t_fd	*fds;

	fds = g_data.fds;
	while (fds)
	{
		if (fds->value != node->fd_in && fds->value != node->fd_out)
			close(fds->value);
		fds = fds->next;
	}
	dup2(node->fd_in, STDIN_FILENO);
	if (node->fd_out != 0)
		dup2(node->fd_out, STDOUT_FILENO);
	exec_extern_cmd(node);
}

void	exec_commands(void)
{
	t_node	*node;
	pid_t	pid;

	node = g_data.node;
	link_relation();
	while (node)
	{
		if (!node->is_file)
		{
			close_prev_fd(node);
			pid = fork();
			if (pid == 0)
				execute_cmd(node);
			waitpid(pid, NULL, 0);
		}
		node = node->next;
	}
}
