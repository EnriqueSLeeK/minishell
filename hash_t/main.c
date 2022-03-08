#include <stdio.h>
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

# define INIT_SIZE 128
# define FNV_PRIME 1099511628211UL
# define FNV_OFFSET 14695981039346656037UL

typedef struct s_entry
{
	char	*key;
	char	*value;
} t_entry;

typedef struct s_hash_table
{ t_entry	**table;
	int		length;
	int		capacity;
} t_hash_table;

int	set_entry(t_hash_table *table, t_entry *entry);

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

int	free_entry(t_entry **entry)
{
	if (*entry != 0)
	{
		free((*entry) -> key);
		free((*entry) -> value);
		free(*entry);
		*entry = 0;
		return (-1);
	}
	return (0);
}

void	free_table(t_hash_table **table)
{
	int	i;

	i = 0;
	while (i < (*table) -> capacity)
	{
		free_entry(&((*table) -> table[i]));
		i += 1;
	}
	free((*table) -> table);
	free(*table);
	*table = 0;
}

unsigned long long int	hash(const char *data_byte)
{
	unsigned long long int	key;
	int						i;

	i = 0;
	key = FNV_OFFSET;
	while (data_byte[i])
	{
		key ^= (unsigned long long int)(unsigned char)data_byte[i];
		key *= FNV_PRIME;
		i += 1;
	}
	return (key);
}

int	index_adjust(unsigned long long int index, int capacity)
{
	if (index >= capacity)
		return (0);
	else
		return (index);
}

// If the hash table has a length equals to capacity / 2 then resize it
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

int	update_or_find_null(t_hash_table *table, t_entry *entry, unsigned long long int *i)
{
	while (table -> table[*i] != 0)
	{
		if (ft_strncmp(entry -> key, table -> table[*i] -> key, ft_strlen(entry -> key)) == 0)
		{
			free(table -> table[*i] -> value);
			table -> table[*i] -> value = ft_strdup(entry -> value);
			free_entry(&entry);
			return (1);
		}
		*i = index_adjust(*i + 1, (unsigned long long int)table -> capacity);
	}
	return (0);
}

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

t_entry	**get_entry(t_hash_table *table, char *key)
{
	int	i;

	i = hash(key) % table -> capacity;
	while (table -> table[i] != 0)
	{
		if (ft_strncmp(key, table -> table[i] -> key, ft_strlen(key)) == 0)
			return (&(table -> table[i]));
		i += 1;
	}
	return (0);
}

void	print_elem(t_hash_table *table, char *key)
{
	t_entry	**entry;

	entry = get_entry(table, key);
	if (entry != 0)
		printf("%s=%s\n", (*entry) -> key, (*entry) -> value);
}

void	remove_entry(t_hash_table *table, char *key)
{
	t_entry	**entry;

	entry = get_entry(table, key);
	if (entry != 0)
		table -> length += free_entry(entry);
}

int	find_equal(char *env)
{
	int	s;

	s = 0;
	while (env[s])
	{
		if (env[s] == '=')
			return (s);
		s += 1;
	}
	return (-1);
}

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

int	main(void)
{
	t_hash_table	*table;
	t_entry			**entry;

	table = ht_create();
	set_entry(table, create_entry("test_1", "12")); // Insere ou atualiza caso exista
	set_entry(table, create_entry("test_1", "13"));
	set_entry(table, create_entry("test_1", "99999"));
	set_entry(table, create_entry("aaa", "123"));
	set_entry(table, create_entry("test_4", "aaaaa"));
	set_entry(table, create_entry("a", ""));
	list_all(table);
	free_table(&table); // Libera a table e os elementos
	return (0);
}
