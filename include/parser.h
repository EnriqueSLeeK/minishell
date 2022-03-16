/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:02:51 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/03/16 10:38:19 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "shell.h"

# define TRUE 1
# define FALSE 0
# define QUOTE '\''
# define DOUBLE_QOUTE '"'

typedef struct s_command {
	char				**args;
	char				*relation;
	char				*complet_instruct;
	int					input;
	int					output;
	struct s_command	*next;
	struct s_command	*previous;
}	t_command;

void		create_relation(char *line);

/*Functions to create a new command node */

t_command	*parse_command(char *command);
void		create_new_command_node(t_command *new_command);
void		create_command(char *command, char *relation);
char		*create_node(char *line, int index, int first, char *relation);

/*Functions to clear memory from commmand node and operators array*/

void		free_args(t_command *command);
void		free_operations(void);
void		free_commands(void);

#endif