/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 10:19:45 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/05/09 19:05:36 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void sub_shell(t_node *node)
{
    char    *line;

    line = ft_strdup(node->sub_line);
    dup2(node->fd_in, STDIN_FILENO);
    dup2(node->fd_out, STDOUT_FILENO);
    var_expansion_line(&line, EXPAND_ALL);
    free_commands();
    ft_parse(line);
    link_relation();
    free(line);
    star_expansion(g_data.node);
    if (!check_grammar() && g_data.node)
        exec_commands();
    clean_up();
    exit(g_data.exit_code);
}

void verify_node(t_node *node, int *status)
{
    int id;

    if (node->sub_line != NULL)
    {
        id = fork();
        if (id == 0)
            sub_shell(node);
        waitpid(id, status, 0);
        child_clean_up(0, 0);
    }
    if (node->fd_in != 0 && node->args[0])
		dup2(node->fd_in, STDIN_FILENO);
	if (node->fd_out != 1 && node->args[0])
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
		child_clean_up(0, 1);
}