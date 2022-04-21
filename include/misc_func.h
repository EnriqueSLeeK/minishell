/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_func.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 15:27:22 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/20 15:51:02 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISC_FUNC_H
# define MISC_FUNC_H

// Quote flag interpretation
typedef struct s_parse_flag
{
	int	sp_quote;
	int	db_quote;
	int	segment_flag;
}	t_parse_flag;

// Quote resolution
char	*quote_resolution(char *line, int *flag);

// Just some general purpose functions
void	free_bmatrix(char **str);
int		find_char(char *str, char c);

// Skip segment
void	skip_segment(char **line);

#endif
