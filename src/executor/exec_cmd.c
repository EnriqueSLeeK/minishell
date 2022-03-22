/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 10:26:57 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/03/22 10:36:04 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/* void exec_bultin(t_command *cmd)
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

void	exec_cmd(t_command *cmd, char *envp[])
{
	if(cmd->builtin == TRUE && !cmd->next)
			exec_bultin(cmd);
	if(cmd->relation && !ft_strncmp(cmd->relation, "|", 1))
		handle_single_pipe(cmd);
	dup2(cmd->input, STDIN_FILENO);
	dup2(cmd->output, STDOUT_FILENO);
	execve(cmd->args[0], cmd->args, envp);
}

void	make_command(char *envp[])
{
	int		id;
	int		status;
	char	*str;
	t_command *cmd;
	
	cmd = g_data.commands;
	printf("quer graça executor?\n");
	while(cmd)
	{
		id = fork();
		if (id == 0)
		{
			exec_cmd(cmd, envp);
		}
		else {
			str = "a porra do pai tem que esperar o filho caralho\n";	
			envp++;
		}
		if(id != 0)
			waitpid(id, &status, 0);
		cmd = cmd->next;
	}
	printf("%s\n",str);
}	 */