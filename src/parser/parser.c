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

void	ft_create_cmd(char *line, char *relation);

void	ft_print();

void	ft_destroy_list();

void	ft_pipe();

char	*is_in(char **operators, char *line)
{
	while (*operators)
	{
		if (!ft_strncmp(*operators, line, ft_strlen(*operators)))
			return (*operators);
		operators++;
	}
	return (0);
}

void	ft_parse(char *line, char **envp)
{
	int		index;
	char	*relation;

	index = 0;
	g_data.pipe_count = 0;
	while(line[index] != '\0')
	{
		relation = is_in(g_data.operators, &line[index]);
		if (relation)
		{
			line[index] = '\0';
			ft_create_cmd(line, relation);
			line += index + 1;
			index = 0;
			g_data.pipe_count++;
		}
		index++;
	}
	relation =  NULL;
	ft_create_cmd(line, 0);
	ft_pipe();
	free_commands();
	(void)envp;
}

/* 
	para cada comando
	abrir a relação de input e output
	com o dup2();
 */

void	ft_create_cmd(char *line, char *relation)
{
	t_node *node;
	t_node *last;

	last = g_data.node;
	node = (t_node *)malloc(sizeof(t_node));
	node->args = ft_split(line, ' ');
	node->relation = relation;
	node->next = NULL;
	node->previous = NULL;
	node->fd_in = 0;
	node->fd_out = 0;
	search_bin(node->args);
	if(last != NULL)
	{
		while(last->next)
			last = last->next;
		last->next = node;
		node->previous = last;
	}
	else
		g_data.node = node;
}

void add_fd(int fd)
{
	t_fd	*new_fd;
	t_fd	*last_fd;

	new_fd = (t_fd *)ft_calloc(sizeof(t_fd), 1);
	new_fd->value = fd;
	last_fd = g_data.fds;
	if(last_fd == NULL)
		g_data.fds = new_fd;
	else 
	{
		while (last_fd->next)
			last_fd = last_fd->next;
		last_fd->next = new_fd;
	}
}

void	handle_red_output(t_node *node)
{
	node->fd_out = open(node->next->args[0], O_CREAT | O_WRONLY | O_TRUNC, 0666);
}

int	handle_pipe(t_node *node)
{
	int	fd[2];

	if(pipe(fd) == -1)
		return (1);
	add_fd(fd[0]);
	add_fd(fd[1]);
	if(node->next)
		node->next->fd_in = fd[0];
	if(node && node->fd_out == 0)
		node->fd_out = fd[1];
	else
		close(fd[1]);
	return (0);
}

void	link_relation()
{
	t_node	*node;

	node = g_data.node;
	while(node)
	{
		if(node->relation)
		{
			if(!ft_strncmp(node->relation, "|", ft_strlen(node->relation)))
				handle_pipe(node);
			else if(!ft_strncmp(node->relation, ">", ft_strlen(node->relation)))
				handle_red_output(node);
		}
		node = node->next;
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

void	close_fd(int fd)
{
	t_fd *fds;

	if(fd == STDIN_FILENO || fd == STDOUT_FILENO)
		return ;
	fds = g_data.fds;
	while(fds)
	{
		if(fds->value == fd)
			close(fds->value);
		fds = fds->next;
	}
}

void close_prev_fd(t_node *node)
{
	if(node->previous)
	{
		close_fd(node->previous->fd_in);
		close_fd(node->previous->fd_out);
	}
}

void	ft_parent_process(int *fd, int pid)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	waitpid(pid, NULL, 0);
}

void	exec_extern_cmd(t_node *node)
{
	g_data.exit_code = execve(node->args[0], node->args, g_data.envp);
	exit(15);
}


void	execute_cmd(t_node *node)
{
	t_fd *fds;

	fds = g_data.fds;
	while(fds)
	{
		if(fds->value != node->fd_in && fds->value != node->fd_out)
			close(fds->value);
		fds = fds->next;
	}
	dup2(node->fd_in, STDIN_FILENO);
	if(node->fd_out != 0)
		dup2(node->fd_out, STDOUT_FILENO);
	exec_extern_cmd(node);
}

void	exec_commands(void)
{
	t_node	*node;
	pid_t	pid;

	node = g_data.node;
	while(node)
	{
		close_prev_fd(node);
		pid = fork();
		if(pid == 0)
			execute_cmd(node);
		waitpid(pid, NULL, 0);
		node = node->next;
	}
}

void	ft_pipe()
{
	pid_t	pid;

	pid = fork();
	if(pid == 0)
	{
		link_relation();
		exec_commands();
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