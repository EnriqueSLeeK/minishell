/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:08:00 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/16 10:00:07 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_shell	g_data;

static void	init_signal(void);
static void	interrupt_handler(int sig);
static void	init_operators(void);
void		init(int argc, char *argv[], char *envp[]);

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;

	init(argc, argv, envp);
	while (1)
	{
		line = prompt();
		create_relation(line);
		search_bin(&(g_data.commands->args[0]));
		printf("command path = %s\n", g_data.commands->args[0]);
		free_commands();
		free(line);
	}
	return (0);
}

void	init(int argc, char *argv[], char *envp[])
{
	if (argc == 1 && argv[argc] == 0)
	{
		init_signal();
		init_env_table(envp);
		g_data.exit_code = 0;
		init_operators();
	}
	else
		exit(1);
}

// SIGQUIT = ctrl + \ must be ignored
// SIGINT = ctrl + c will call the function interrupt_handler
static void	init_signal(void)
{
	signal(SIGINT, interrupt_handler);
	signal(SIGQUIT, SIG_IGN);
}

static void	interrupt_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
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
