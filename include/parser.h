/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:02:51 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/03/11 11:44:19 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
#include "shell.h"

typedef struct s_cmd {
	char	*cmd;
	char	**args;
	char	*relation;
	struct s_cmd *next;
} t_cmd;


void	parser_line(char *line, t_cmd *cmd_list);

#endif