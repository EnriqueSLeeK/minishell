/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:59:42 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/07 23:01:33 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	clean_up(void)
{
	free_table(&g_data.env_vars);
	free_table(&g_data.local_vars);
	rl_clear_history();
}
