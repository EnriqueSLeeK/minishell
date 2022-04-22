/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 10:26:57 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/04/22 11:59:58 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// Clean up data if execve fails
void	exec_extern_cmd(t_node *node)
{
	g_data.envp = convert_table_matrix(g_data.env_vars);
	g_data.exit_code = execve(node->args[0], node->args, g_data.envp);
	show_error(M_COMMAND_NOT_FOUND, node->args[0], 2, 0);
	child_clean_up(g_data.envp);
	exit(127);
}

int	exec_bultin(t_node *node)
{
	if (!ft_strncmp(node->args[0], "echo", 4))
		return (echo(node->args));
	else if (!ft_strncmp(node->args[0], "env", 3))
		return (env());
	else if (!ft_strncmp(node->args[0], "cd", 2))
		return (cd(node->args));
	else if (!ft_strncmp(node->args[0], "exit", 4))
		b_exit();
	else if (!ft_strncmp(node->args[0], "export", 6))
		return (export(node->args));
	else if (!ft_strncmp(node->args[0], "pwd", 3))
		return (pwd());
	else if (!ft_strncmp(node->args[0], "unset", 5))
		return (unset(&(node->args[1])));
	return (1);
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
	if (node->is_builtin)
	{
		g_data.exit_code = exec_bultin(node);
		clean_up();
		exit(g_data.exit_code);
	}
	else if (node->args[0])
		exec_extern_cmd(node);
	else
	{
		child_clean_up(0);
		exit(1);
	}
}

void	exec_commands(void)
{
	t_node	*node;
	pid_t	pid;

	node = g_data.node;
	if (node->is_builtin && !node->next && g_data.status != CANCEL)
		g_data.exit_code = exec_bultin(node);
	else if (g_data.status != CANCEL)
	{
		exec_sig(&(g_data.sig));
		while (node && node->fd_in != -1)
		{
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
}

int	check_grammar(void)
{
	t_node	*node;
	char	*buffer;

	node = g_data.node;
	buffer = NULL;
	if (!node)
		return (1);
	while (node)
	{
		if (buffer)
			free(buffer);
		if (check_next_relation(node))
			return (1);
		buffer = get_full_instruction(node);
		if (check_quotes(buffer))
		{
			free(buffer);
			return (1);
		}
		node = node->next;
	}
	free(buffer);
	return (0);
}
