/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 10:26:57 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/03/17 10:22:09 by mamaro-d         ###   ########.fr       */
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
			export(cmd->args[0], cmd->args[1]);
		if (!(ft_strncmp(cmd->args[0], "env", 3)))
			env();
		if (!(ft_strncmp(cmd->args[0], "unset", 5)))
			unset(cmd->args[1]);
}


void	make_command(void)
{
	if(g_data.commands->builtin == TRUE && !g_data.commands->next)
		exec_bultin(g_data.commands);
}