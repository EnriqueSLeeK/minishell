/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_var.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 13:48:41 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/05 19:18:41 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIN_VAR_H
# define BIN_VAR_H

# define EXPAND_ALL 1
# define EXPAND_ONE 2

// Var utils
// Do not use status_code directly use var_expansion instead
char	*status_code(void);
int		local_var(char **arg);
int		check_varname(char *var);
void	var_expansion(char ***parsed_line, int flag);
void	wild_expansion(char ***parsed_line, int i, int k);

// Bin utils
int		search_bin(char **bin);

#endif
