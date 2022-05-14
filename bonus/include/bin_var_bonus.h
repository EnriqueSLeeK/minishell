/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_var_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 13:48:41 by ensebast          #+#    #+#             */
/*   Updated: 2022/05/14 15:25:49 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIN_VAR_BONUS_H
# define BIN_VAR_BONUS_H

# define EXPAND_ALL 1
# define EXPAND_ONE 2

// Flags to check if is expandable or not
# define IGNORE 0
# define EXPAND 1

// Lock expantion for $
# define LOCK_E 2

// Operator arg
# define OP_ARG 4

// Var utils
// Do not use status_code directly use var_expansion instead
char	*status_code(void);
int		local_var(char **arg);
int		check_varname(char *var);
void	expand_mix(char **parsed_line, int flag);
void	var_expansion_list(char **parsed_line, int flag);
void	var_expansion_line(char **parsed_line, int flag);

// Bin utils
int		search_bin(char **bin);

#endif
