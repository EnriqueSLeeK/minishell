/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:05:26 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/03/13 16:26:11 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init_cmd_lst(t_cmd *cmd_lst)
{
	cmd_lst = (t_cmd *)malloc(sizeof(t_cmd));
	cmd_lst->next = NULL;
}

void	add_new_cmd(t_cmd **cmd_lst, char *cmd, char **args)
{
	(*cmd_lst)->next = (t_cmd *)malloc(sizeof(t_cmd));
	*cmd_lst = (*cmd_lst)->next;
	(*cmd_lst)->cmd = cmd;
	(*cmd_lst)->args = args;
}

/* void verify_pipes(char *line)
{
	int	i;

	i = 0;
	while(i < ft_strlen(line))
	{
		if(line[i] == '|')
			printf("Achei um pipe em %d\n", i + 1);
		i++;
	}
}

void verify_redirects(char *line)
{
	int	i;

	i = 0;
	while(i < ft_strlen(line))
	{
		if(line[i] == '<')
			printf("Input file em %d\n", i + 1);
		else if (line[i] == '>')
			printf("Out file em %d\n", i + 1);
		i++;
	}
}

void verify_cmds(char *line, t_cmd **cmd_list)
{
	
}

void verify_here_doc(char *line)
{
	int	i;

	i = 0;
	while(i < ft_strlen(line))
	{
		if(!ft_strncmp(line, "<<", 2))
			printf("Here doc na linha %d\n", i + 1);
		i++;
	}
}
 */
int	is_in(char arr[6][3], char *line)
{
	int	i;

	i = 0;
	while(i < 6)
	{
		if(!ft_strncmp(arr[i], line, ft_strlen(arr[i])))
		{
			return (1);
		}
		i++;	
	}
	return (0);
}


void	parser_line(char *line, t_command *cmd_list)
{
	int	i;
	char	operations[7][3] = {">", "|", "<", ">>", "<<", "\n", 0};

	i = 0;
	while (line[i])
	{
		if(is_in(operations, &line[i]))
		{
			line[i] = 0;
			printf("Operator %s\n", line);
			line += i + 1;
			i = 0;
			continue ;
		}
		i++;
	}
	printf("Operation = %s\n", line);
}