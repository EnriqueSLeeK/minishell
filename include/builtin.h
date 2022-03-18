/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 18:24:21 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/17 14:58:50 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

int		env(void);
int		cd(char **args);
int		unset(char *key);
int		echo(char **args);
int		export(char **args);
void	b_exit(void);
int		pwd(void);

#endif
