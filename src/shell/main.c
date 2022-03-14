/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:08:00 by ensebast          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/03/13 16:17:37 by mamaro-d         ###   ########.fr       */
=======
/*   Updated: 2022/03/13 22:37:38 by ensebast         ###   ########.fr       */
>>>>>>> e422dc5da860870205ab75ad6357180c44c77f60
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_shell	g_data;

static void	init_signal(void);
static void	interrupt_handler(int sig);
void		init(int argc, char *argv[], char *envp[], t_cmd *cmd);

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
<<<<<<< HEAD
	t_cmd	cmds;
	init(argc, argv,envp);
=======
	t_cmd	cmd_info;

	init(argc, argv, envp, &cmd_info);
>>>>>>> e422dc5da860870205ab75ad6357180c44c77f60
	while (1)
	{
		line = prompt();
		parser_line(line, &cmds);
		free(line);
	}
	return (0);
}

void	init(int argc, char *argv[], char *envp[], t_cmd *cmd)
{
	if (argc == 1 && argv[argc] == 0)
	{
		init_signal();
		init_env_table(envp);
		g_data.exit_code = 0;
		cmd -> cmd = 0;
		cmd -> bin_with_path = 0;
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
