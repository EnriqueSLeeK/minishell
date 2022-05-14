/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:42:03 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/07 23:05:01 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H

# define INIT_SIZE 128
# define FNV_PRIME 1099511628211UL
# define FNV_OFFSET 14695981039346656037UL

typedef struct s_entry
{
	char	*key;
	char	*value;
}	t_entry;

typedef struct s_hash_table
{
	t_entry	**table;
	int		length;
	int		capacity;
}	t_hash_table;

// Table related functions
t_hash_table			*ht_create(void);
int						expand_table(t_hash_table *table);
void					free_table(t_hash_table **table);

// Entry related functions
t_entry					*create_entry(char *key, char *value);
t_entry					**get_entry(t_hash_table *table, char *key);
int						set_entry(t_hash_table *table, t_entry *entry);
int						free_entry(t_entry **entry);
void					remove_entry(t_hash_table *table, char *key);

// Hashing algorithm
// If a collision occurs we will use linear probing to solve it
unsigned long long int	hash(const char *data_byte);

// Misc functions
void					list_all(t_hash_table *table);
char					*get_value(t_hash_table *table, char *key);
void					print_elem(t_hash_table *table, char *key);
int						index_adjust(unsigned long long int index,
							unsigned long long int capacity);
int						update_or_find_null(t_hash_table *table,
							t_entry *entry, unsigned long long int *i);

#endif
