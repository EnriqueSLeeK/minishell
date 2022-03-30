/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:08:00 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/30 13:16:38 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_shell	g_data;

static void	init_operators(void);
void		init(int argc, char *argv[], char *envp[]);

int	main(int argc, char *argv[], char *envp[])
{
	char		*line;
	char		**env;
	t_signal	sig;

	init(argc, argv, envp);
	while (1)
	{
		prompt_sig(&sig);
		line = prompt();
		create_relation(line);
		if (!g_data.commands->builtin)
			search_bin(&(g_data.commands->args[0]));
		env = convert_table_matrix();
		if (env != 0)
			make_command(env);
		post_exec_clean(line, env);
	}
	return (0);
}

// SIGQUIT = ctrl + \ must be ignored
// SIGINT = ctrl + c will call the function interrupt_handler
void	init(int argc, char *argv[], char *envp[])
{
	if (argc == 1 && argv[argc] == 0)
	{
		g_data.exit_code = 0;
		init_env_table(envp);
		init_operators();
	}
	else
		exit(1);
}

static void	init_operators(void)
{
	g_data.operators = (char **)ft_calloc(6, sizeof(char *));
	g_data.operators[0] = ft_strdup("|");
	g_data.operators[1] = ft_strdup(">");
	g_data.operators[2] = ft_strdup("<");
	g_data.operators[3] = ft_strdup(">>");
	g_data.operators[4] = ft_strdup("<<");
}
