/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_var.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 13:48:41 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/13 17:11:27 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIN_VAR_H
# define BIN_VAR_H

# define EXPAND_ALL 1
# define EXPAND_ONE 2

# define EXPAND 1
# define IGNORE 0
# define LOCK_E 2

// Var utils
// Do not use status_code directly use var_expansion instead
char	*status_code(void);
int		local_var(char **arg);
int		check_varname(char *var);
void	expand_mix(char **parsed_line, int flag);
void	var_expansion(char **parsed_line, int flag);

// Bin utils
int		search_bin(char **bin);

#endif
