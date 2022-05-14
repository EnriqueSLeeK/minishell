/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 10:26:57 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/05/14 15:11:48 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_bonus.h"

// Clean up data if execve fails
void	exec_extern_cmd(t_node *node)
{
	g_data.envp = convert_table_matrix(g_data.env_vars);
	execve(node->args[0], node->args, g_data.envp);
	show_error(M_COMMAND_NOT_FOUND, node->args[0], 2, 0);
	child_clean_up(g_data.envp, 127);
}

int	exec_bultin(t_node *node)
{
	if (!ft_strncmp(node->args[0], "echo", ft_strlen(node->args[0])))
		return (echo(node->args));
	else if (!ft_strncmp(node->args[0], "env", ft_strlen(node->args[0])))
		return (env());
	else if (!ft_strncmp(node->args[0], "cd", ft_strlen(node->args[0])))
		return (cd(node->args));
	else if (!ft_strncmp(node->args[0], "exit", ft_strlen(node->args[0])))
		b_exit();
	else if (!ft_strncmp(node->args[0], "export", ft_strlen(node->args[0])))
		return (export(node->args));
	else if (!ft_strncmp(node->args[0], "pwd", ft_strlen(node->args[0])))
		return (pwd());
	else if (!ft_strncmp(node->args[0], "unset", ft_strlen(node->args[0])))
		return (unset(&(node->args[1])));
	return (1);
}

void	execute_cmd(t_node *node)
{
	t_fd	*fds;
	int		status;

	fds = g_data.fds;
	child_sig(&(g_data.sig));
	while (fds)
	{
		if (fds->value != node->fd_in && fds->value != node->fd_out)
			close(fds->value);
		fds = fds->next;
	}
	verify_node(node, &status);
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
			if (!node->is_file && node->args[0])
			{
				pid = fork();
				if (pid == 0)
					execute_cmd(node);
				waitpid(pid, &g_data.exit_code, 0);
				g_data.exit_code = get_status(g_data.exit_code);
			}
			node = get_next_node(node);
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
		can_trim(node);
		node = node->next;
	}
	free(buffer);
	return (0);
}
