/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:09:28 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/13 17:11:17 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_BONUS_H
# define WILDCARD_BONUS_H

// Misc Utils
int		match_exp(char *regexp, char *text);

// Core functions
void	expand_wild(char ***line, int i);
void	we_pre_split(char **line, int index);
void	get_list_filter(char *exp, char ***file_list);

#endif
