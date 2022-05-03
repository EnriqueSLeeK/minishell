/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relations_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 11:18:34 by mamaro-d          #+#    #+#             */
/*   Updated: 2022/05/03 19:11:17 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int     get_line_len(char *line)
{
    int index;
    int count;

    index = 1;
    count = 1;
    while (line[index])
    {
        if (line[index] == '(')
            count++;
        if (line[index] == ')')
            count--;
        if (!count)
            break ;
        index++;
    }
    return (index);
}

char    *create_subshell(char *line)
{
    t_node  *node;
    char    *relation;
    char    *sub_line;

    sub_line = (char *)ft_calloc(get_line_len(line), sizeof(char));
    ft_strlcpy(sub_line, &line[1], get_line_len(line));
    relation = is_in(g_data.operators, line);
    if (*line && !relation)
    {
        line++;
        relation = is_in(g_data.operators, line);
    }
    if(*line)
        line += ft_strlen(relation);
    node = (t_node *)ft_calloc(sizeof(t_node), 1);
    node->args = ft_split("subshell", ' ');
    node->relation = relation;
    node->sub_line = sub_line;
    add_new_node(node);
    return (line);
}

char    *check_relation(char *line, int *index, int quote)
{
    char    *relation;
    if(line[*index] == '(' && !quote)
    {
        line = create_subshell(&line[*index]);
        *index = 0;
        return (line);
    }
    relation = is_in(g_data.operators, &line[*index]);
    if(relation && !quote)
    {
        line = ft_create_cmd(line, *index,  relation);
        *index = 0;
    }
    else
        *index += 1;
    return (line);
}