/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 10:26:57 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/03/24 14:17:53 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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

//fd[0] read
//fd[1] write
void handle_single_pipe(t_command *cmd)
{
	int	fd[2];
	pipe(fd);
	cmd->output = fd[1];
	cmd->next->input = fd[0];
}

void	make_command(char **envp)
{
	int	id;
	t_command *cmd;

	cmd = g_data.commands;
	while(cmd)
	{
		if(cmd->builtin == TRUE && !cmd->next)
			exec_bultin(cmd);
		else
		{
			id = fork();
			if(cmd->relation && !ft_strncmp(cmd->relation, "|", 1))
				handle_single_pipe(cmd);
			dup2(cmd->input, STDIN_FILENO);
			dup2(cmd->output, STDOUT_FILENO);
			if(id == 0)
			{
				execve(cmd->args[0], cmd->args, envp);
			}
			waitpid(id, &g_data.exit_code, 0);
			cmd = cmd->next;
		}
	}
}
