/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:02:51 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/03/31 16:23:04 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "shell.h"

# define TRUE 1
# define FALSE 0
# define QUOTE '\''
# define DOUBLE_QOUTE '"'

typedef struct s_node
{
	char			**args;
	char			*relation;
	int				fd_in;
	int				fd_out;
	int				is_file;
	int				is_builtin;
	struct s_node	*next;
	struct s_node	*previous;
}	t_node;

typedef struct s_fd
{
	int				value;
	struct s_fd		*next;
}	t_fd;

void	ft_parse(char *line);
char	*is_in(char **operators, char *line);
void	ft_create_cmd(char *line, char *relation);

void	handle_red_output(t_node *node);
int		handle_pipe(t_node *node);
void	handle_red_intput(t_node *node);

void	link_relation(void);
void	add_new_node(t_node *node);

int		is_builtin(t_node *node);
int		is_file(t_node	*node);
void	set_type(t_node *node);

void	free_operations(void);
void	free_commands(void);
#endif