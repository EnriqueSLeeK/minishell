/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_var.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 13:48:41 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/12 14:17:49 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIN_VAR_H
# define BIN_VAR_H

struct typedef s_cmd
{
		char	*bin_with_path;
		char	**cmd;
}	t_cmd;

int		search_bin(char *bin, t_cmd *cmd);
void	var_expansion(char **parsed_line);

#endif
