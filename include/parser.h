/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:02:51 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/04/21 11:17:18 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "shell.h"

# define TRUE 1
# define FALSE 0

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
char	*ft_create_cmd(char *line, int index, char *relation);

void	handle_red_output(t_node *node);
int		handle_pipe(t_node *node);
void	handle_red_input(t_node *node);
void	handle_here_doc(t_node *node);

void	link_relation(void);
void	add_new_node(t_node *node);

int		is_builtin(t_node *node);
int		is_file(t_node	*node);
void	set_type(t_node *node);
char	*get_full_instruction(t_node *node);

void	free_operations(void);
void	free_commands(void);

int		check_next_relation(t_node *node);

int		check_quotes(char *line);
void	has_quote(char *line, char *quote);

#endif