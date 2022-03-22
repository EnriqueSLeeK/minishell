/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:02:51 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/03/22 12:10:02 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "shell.h"

# define TRUE 1
# define FALSE 0
# define QUOTE '\''
# define DOUBLE_QOUTE '"'

typedef struct	s_node
{
	char	**args;
	char	*relation;
	int		fd_in;
	int		fd_out;
	struct s_node	*next;
}	t_node;

void ft_parse(char *line, char **envp);


void	free_operations(void);
#endif