/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 15:23:40 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/17 15:25:28 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// Bidimensional matrix
void	free_bmatrix(char **matrix)
{
	int	i;

	while (matrix[i])
	{
		free(matrix[i]);
		i += 1;
	}
	free(matrix);
}
