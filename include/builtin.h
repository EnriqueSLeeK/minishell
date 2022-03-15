/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 18:24:21 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/15 18:11:47 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

int	env(void);
int	cd(char **args);
int	unset(char *key);
int	echo(char **args);
int	export(char	*key, char *value);

#endif
