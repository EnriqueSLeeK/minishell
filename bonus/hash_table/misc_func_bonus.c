/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_func_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:34:55 by ensebast          #+#    #+#             */
/*   Updated: 2022/05/14 15:11:48 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_bonus.h"

// Get only the value
char	*get_value(t_hash_table *table, char *key)
{
	t_entry	**entry;

	entry = get_entry(table, key);
	if (entry != 0)
		return ((*entry)-> value);
	return (0);
}

// Print all element in the format "KEY=VALUE"
void	list_all(t_hash_table *table)
{
	int		i;
	t_entry	**entry_list;

	i = 0;
	entry_list = table -> table;
	while (i < table -> capacity)
	{
		if (entry_list[i] != 0)
			printf("%s=%s\n", entry_list[i]-> key, entry_list[i]-> value);
		i += 1;
	}
}

// Print element with this format "KEY=VALUE\n"
void	print_elem(t_hash_table *table, char *key)
{
	t_entry	**entry;

	entry = get_entry(table, key);
	if (entry != 0)
		printf("%s=%s\n", (*entry)-> key, (*entry)-> value);
}

// Update the entry or return a index pointing to a empty place
int	update_or_find_null(t_hash_table *h_table, t_entry *entry,
		unsigned long long int *i)
{
	while (h_table -> table[*i] != 0)
	{
		if (ft_strncmp(entry -> key, h_table -> table[*i]-> key,
				ft_strlen(entry -> key)) == 0)
		{
			free(h_table -> table[*i]-> value);
			h_table -> table[*i]-> value = ft_strdup(entry -> value);
			free_entry(&entry);
			return (1);
		}
		*i = index_adjust(*i + 1, (unsigned long long int)h_table -> capacity);
	}
	return (0);
}

// Index adjust to give a circular motion
int	index_adjust(unsigned long long int index, unsigned long long int capacity)
{
	if (index >= capacity)
		return (0);
	else
		return (index);
}
