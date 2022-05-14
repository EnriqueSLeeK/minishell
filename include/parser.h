/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:02:51 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/05/14 14:25:49 by mamaro-d         ###   ########.fr       */
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
	char			*sub_line;
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

char	*swap_char(char *line, char old_char, char new_char);
char	**swap_char_matrix(char **matrix);

int		check_quoute(char c, int *is_active, char *quoute);
char	*copy_string_trim(char **matrix, int j, int *is_active, char *quoute);
void	trim_quotes(char **matrix);
void	can_trim(t_node *node);

#endif