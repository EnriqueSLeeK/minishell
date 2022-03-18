/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 10:26:57 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/03/18 09:47:17 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	add_fd(int fd)
{
	t_fd	*new_fd;
	t_fd	*all_fds;

	new_fd = (t_fd *)ft_calloc(sizeof(t_fd), 1);
	new_fd->value = fd;
	all_fds = g_data.all_fd;
	if(all_fds == 0)
		g_data.all_fd = new_fd;
	else
	{
		while(all_fds->next)
			all_fds = all_fds->next;
		all_fds->next = new_fd;
	}
}

int		is_cmd(t_command *cmd)
{
	if (cmd->previous == 0 && cmd->args[0])
		return (1);
	if (cmd->previous == 0)
		return (0);
	if (cmd->previous->relation && cmd->previous->relation[0] == '|')
		return (1);
	if (cmd->previous->relation && cmd->previous->relation[0] == ' ')
		return (1);
	if (cmd->relation == 0 && cmd->previous->relation[0] == '|')
		return (1);
	return (0);
}

void	handle_pipe(t_command *cmd)
{
	int		fd[2];

	if(pipe(fd) == -1)
		return (1);
	add_fd(fd[0]);
	add_fd(fd[1]);
	cmd->next->input = fd[0];
	while (cmd && !is_cmd(cmd))
		cmd = cmd->previous;
	if (cmd && cmd->output == 0)
		cmd->output = fd[1];
	else
		close(fd[1]);
	return (0);
}

void	link_relations(void)
{
	t_command *cmd;

	cmd = g_data.commands;
	while(cmd)
	{
		if (cmd->relation == 0)
			break ;
		else if (cmd->relation[0] == '|')
			handle_pipe(cmd);
		cmd = cmd->next;
	}
}

void exec_bultin(t_command *cmd)
{
	if (!(ft_strncmp(cmd->args[0], "exit", 4)))
			b_exit();
	if (!(ft_strncmp(cmd->args[0], "echo", 4)))
		echo(cmd->args);
	if (!(ft_strncmp(cmd->args[0], "cd", 2)))
		cd(cmd->args);
	if (!(ft_strncmp(cmd->args[0], "pwd", 3)))
		pwd();
	if (!(ft_strncmp(cmd->args[0], "export", 6)))
		export(cmd->args);
	if (!(ft_strncmp(cmd->args[0], "env", 3)))
		env();
	if (!(ft_strncmp(cmd->args[0], "unset", 5)))
		unset(cmd->args[1]);
}

void	close_prev_fd(t_command *cmd)
{
	if (cmd->previous && is_command(cmd->previous))
	{
		close_fd(cmd->previous->input);
		close_fd(cmd->previous->output);
	}
}

void	exec_cmd(void)
{
	int			status;
	t_command	*cmd;
	int			id;

	status = 0;
	cmd = g_data.commands;
	while(cmd)
	{
		close_prev_fd(cmd);
		if(is_cmd(cmd))
		{
			id = fork();
			if(id == 0)

		}
	}
}

void	make_command(void)
{
	int	id;
	if(g_data.commands->builtin == TRUE && !g_data.commands->next)
		exec_bultin(g_data.commands);
	else
	{
		id = fork();
		if(id == 0)
		{
			link_relations();
		}
	}
}
