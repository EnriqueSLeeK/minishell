/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:38:54 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/08 16:53:19 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	unset(char *key)
{
	remove_entry(g_data.local_vars, key);
	remove_entry(g_data.env_vars, key);
	return (0);
}
