/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:30:24 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/17 10:03:06 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	b_exit(void)
{
	clean_up();
	exit(0);
}
