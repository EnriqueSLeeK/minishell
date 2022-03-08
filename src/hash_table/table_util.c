/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:23:21 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/07 20:33:33 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// Just create a table
t_hash_table	*ht_create(void)
{
	t_hash_table	*table;

	table = malloc(sizeof(t_hash_table));
	if (table == 0)
		return (0);
	table -> length = 0;
	table -> capacity = INIT_SIZE;
	table -> table = ft_calloc(table -> capacity, sizeof(t_entry));
	if (table -> table == 0)
	{
		free(table);
		return (0);
	}
	return (table);
}

// Free table and the entries
void	free_table(t_hash_table **table)
{
	int	i;

	i = 0;
	while (i < (*table)-> capacity)
	{
		free_entry(&((*table)-> table[i]));
		i += 1;
	}
	free((*table)-> table);
	free(*table);
	*table = 0;
}

// Double the size of the table and transfer elements to the new table
int	expand_table(t_hash_table *table)
{
	t_entry	**tmp_table;
	int		i;

	i = 0;
	tmp_table = table -> table;
	table -> table = ft_calloc(table -> capacity * 2, sizeof(t_entry));
	if (table -> table == 0)
		return (0);
	table -> capacity *= 2;
	table -> length = 0;
	while (i < table -> capacity)
	{
		if (tmp_table[i] != 0)
			set_entry(table, tmp_table[i]);
		i += 1;
	}
	free(tmp_table);
	return (1);
}
