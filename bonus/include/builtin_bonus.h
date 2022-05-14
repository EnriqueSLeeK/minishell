/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 18:24:21 by ensebast          #+#    #+#             */
/*   Updated: 2022/05/14 15:27:01 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_BONUS_H
# define BUILTIN_BONUS_H

int		env(void);
int		cd(char **args);
int		unset(char **key);
int		echo(char **args);
int		export(char **args);
void	b_exit(void);
int		pwd(void);

#endif
