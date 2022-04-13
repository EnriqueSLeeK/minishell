/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 10:26:57 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/04/13 10:51:05 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	exec_extern_cmd(t_node *node)
{
	g_data.envp = convert_table_matrix(g_data.env_vars);
	g_data.exit_code = execve(node->args[0], node->args, g_data.envp);
	perror("execve");
	exit(1);
}

void	exec_bultin(t_node *node)
{
	printf("Executando uma bultin\n");
	if (!ft_strncmp(node->args[0], "echo", 4))
		echo(node->args);
	else if (!ft_strncmp(node->args[0], "cd", 2))
		cd(node->args);
	else if (!ft_strncmp(node->args[0], "env", 3))
		env();
	else if (!ft_strncmp(node->args[0], "exit", 4))
		b_exit();
	else if (!ft_strncmp(node->args[0], "export", 6))
		export(node->args);
	else if (!ft_strncmp(node->args[0], "pwd", 3))
		pwd();
	else if (!ft_strncmp(node->args[0], "unset", 5))
		unset(node->args[1]);
}

void	execute_cmd(t_node *node)
{
	t_fd	*fds;

	fds = g_data.fds;
	child_sig(&(g_data.sig));
	while (fds)
	{
		if (fds->value != node->fd_in && fds->value != node->fd_out)
			close(fds->value);
		fds = fds->next;
	}
	dup2(node->fd_in, STDIN_FILENO);
	dup2(node->fd_out, STDOUT_FILENO);
	/* if(node->is_builtin)
		exec_bultin(node);
	else */
		exec_extern_cmd(node);
}

void	exec_commands(void)
{
	t_node	*node;
	pid_t	pid;

	node = g_data.node;
	if (check_grammar())
		return ;
	link_relation();
	exec_sig(&(g_data.sig));
	while (node)
	{
		if (node->fd_in == -1)
			return ;
		close_prev_fd(node);
		if (!node->is_file)
		{
			pid = fork();
			if (pid == 0)
				execute_cmd(node);
			waitpid(pid, NULL, 0);
		}
		node = node->next;
	}
}

int	check_grammar(void)
{
	t_node	*node;

	node = g_data.node;
	while (node)
	{
		if (check_next_relation(node))
			return (1);
		node = node->next;
	}
	return (0);
}
