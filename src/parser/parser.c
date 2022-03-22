/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:53:01 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/03/22 16:36:36 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_pipeline();

void	ft_create_cmd(char *line);

void	ft_print();

void	ft_destroy_list();

void	ft_pipe();

void	ft_parse(char *line, char **envp)
{
	int	index;

	index = 0;
	g_data.pipe_count = 0;
	while(line[index] != '\0')
	{
		if (line[index] == '|')
		{
			line[index] = '\0';
			ft_create_cmd(line);
			line += index + 1;
			index = 0;
			g_data.pipe_count++;
		}
		index++;
	}
	ft_create_cmd(line);
	ft_pipe();
	(void)envp;
	ft_destroy_list();
}

/* 
	para cada comando
	abrir a relação de input e output
	com o dup2();
 */

void	ft_create_cmd(char *line)
{
	t_node *node;
	t_node *last;

	last = g_data.node;
	node = (t_node *)malloc(sizeof(t_node));
	node->args = ft_split(line, ' ');
	node->relation = g_data.operators[0];
	node->next = NULL;
	node->fd_in = 0;
	node->fd_out = 0;
	search_bin(node->args);
	if(last != NULL)
	{
		while(last->next)
			last = last->next;
		last->next = node;
	}
	else
		g_data.node = node;
}

void	ft_print()
{
	t_node	*tmp;
	int		index;
	
	tmp = g_data.node;
	while (tmp != NULL)
	{
		index = -1;
		while(tmp->args[++index] != NULL)
			printf("%s %d\n", tmp->args[index], index);
		tmp = tmp->next;
		puts("");
	}
}

void	ft_destroy_list()
{
	t_node *tmp;
	int index;
	
	tmp = g_data.node;
	while (g_data.node != NULL)
	{
		index = -1;
		while(tmp->args[++index] != NULL)
			free(tmp->args[index]);
		free(tmp->args);
		tmp = g_data.node->next;
		free(g_data.node);
		g_data.node = tmp;
	}
}
/* 
	fd[0] read;
	fd[1] write;
 */


void	ft_child_process(int *fd)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	execve(g_data.node->args[0], g_data.node->args, g_data.envp);
	// if (execve(g_data.node->args[0], g_data.node->args, g_data.envp) == -1)
		
}

void	ft_parent_process(int *fd, int pid)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	waitpid(pid, NULL, 0);
}

void	ft_pipe()
{
	int		fd[2];
	pid_t	pid;
	int		fd_in;
	if (pipe(fd) == -1)
		ft_putstr_fd("Deu ruim no pipe\n", 2);
	
	fd_in = 0;
	while(g_data.node)
	{
		pid = fork();
		if(!pid)
		{
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
			if(g_data.pipe_count)
				dup2(fd[1], STDOUT_FILENO);
			execve(g_data.node->args[0], g_data.node->args, g_data.envp);
		}
		else
		{
			waitpid(pid, NULL, 0);
			fd_in = dup(fd[0]);
			if(g_data.pipe_count)
			{
				close(fd[1]);
				pipe(fd);
				g_data.pipe_count--;
			} 
			g_data.node = g_data.node->next;
		}
	}
	waitpid(pid, NULL, 0);
}

void	ft_pipeline()
{
	int		fd[2];
	pid_t	pid;
	//pid_t	holder;

	if (pipe(fd) == -1)
		ft_putstr_fd("Deu ruim no pipe\n", 2);
	pid = fork();
	if (pid == -1)
		ft_putstr_fd("Deu ruim no fork 1\n", 2);
	if (!pid)
	{
		ft_child_process(fd);
		/* holder = fork();
		if (holder == -1)
			ft_putstr_fd("Deu ruim no fork 2\n", 2);
		if (!holder)
			
		else
		g_data.node = g_data.node->next; */
		
	}
	else
		ft_parent_process(fd, pid);
	execve(g_data.node->args[0], g_data.node->args, g_data.envp);

	// g_data.node = g_data.node->next;
	// execve(g_data.node->args[0], g_data.node->args, g_data.envp);
}