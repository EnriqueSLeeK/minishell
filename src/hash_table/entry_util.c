/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:28:46 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/07 21:57:35 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// Create a entry
t_entry	*create_entry(char *key, char *value)
{
	t_entry	*entry;

	entry = malloc(sizeof(t_entry));
	if (entry == 0)
		return (0);
	if (ft_strlen(key) > 0)
	{
		entry -> key = ft_strdup(key);
		if (entry -> key == 0)
		{
			free(entry);
			return (0);
		}
		entry -> value = ft_strdup(value);
		if (entry -> value == 0)
		{
			free(entry -> key);
			free(entry);
			return (0);
		}
		return (entry);
	}
	else
		free(entry);
	return (0);
}

// Set a entry or update it
// Return values : 1 -> inserted value; 2 -> updated value, 0 -> failure
int	set_entry(t_hash_table *table, t_entry *entry)
{
	unsigned long long int	index;	

	if (entry == 0)
		return (0);
	index = hash(entry -> key) % table -> capacity;
	if (update_or_find_null(table, entry, &index))
		return (2);
	table -> length += 1;
	table -> table[index] = entry;
	if (table -> length >= (int)(table -> capacity / 2))
	{
		if (expand_table(table) == 0)
		{
			printf("Not enought memory\n");
			return (0);
		}
	}
	return (1);
}

// Get a entry from the table
t_entry	**get_entry(t_hash_table *table, char *key)
{
	int	i;

	i = hash(key) % table -> capacity;
	while (table -> table[i] != 0)
	{
		if (ft_strncmp(key, table -> table[i]-> key, ft_strlen(key)) == 0)
			return (&(table -> table[i]));
		i += 1;
	}
	return (0);
}

// Just free up the entry
int	free_entry(t_entry **entry)
{
	if (*entry != 0)
	{
		free((*entry)-> key);
		free((*entry)-> value);
		free(*entry);
		*entry = 0;
		return (-1);
	}
	return (0);
}

// Will search and delete the entry
void	remove_entry(t_hash_table *table, char *key)
{
	t_entry	**entry;

	entry = get_entry(table, key);
	if (entry != 0)
		table -> length += free_entry(entry);
}
