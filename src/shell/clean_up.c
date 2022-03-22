/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:59:42 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/22 12:08:11 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	clean_up(void)
{
	free_table(&g_data.env_vars);
	free_table(&g_data.local_vars);
	free_operations();
	rl_clear_history();
}
