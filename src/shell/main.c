/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:08:00 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/26 12:06:31 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_shell	g_data;

static void	init_operators(void);
void		init(int argc, char *argv[], char *envp[]);

int	main(int argc, char *argv[], char *envp[])
{
	char		*line;

	init(argc, argv, envp);
	while (1)
	{
		prompt_sig(&(g_data.sig));
		line = prompt();
		var_expansion_line(&line, EXPAND_ALL);
		ft_parse(line);
		link_relation();
		if (!check_grammar() && g_data.node)
			exec_commands();
		post_exec_clean(line);
	}
	return (0);
}

// SIGQUIT = ctrl + \ must be ignored
// SIGINT = ctrl + c will call the function interrupt_handler
void	init(int argc, char *argv[], char *envp[])
{
	if (argc == 1 && argv[argc] == 0)
	{
		g_data.status = CONTINUE;
		g_data.exit_code = 0;
		init_env_table(envp);
		init_operators();
	}
	else
		exit(1);
}

static void	init_operators(void)
{
	g_data.operators = (char **)ft_calloc(8, sizeof(char *));
	g_data.operators[0] = ft_strdup("|");
	g_data.operators[1] = ft_strdup(">>");
	g_data.operators[3] = ft_strdup("<<");
	g_data.operators[2] = ft_strdup(">");
	g_data.operators[4] = ft_strdup("<");
	g_data.operators[5] = NULL;
	g_data.operators[6] = ft_strdup(" ");
}

int	get_status(int status)
{
	return (((status) & 0xff00) >> 8);
}
