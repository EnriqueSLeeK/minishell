/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 13:44:03 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/05 19:11:36 by mamaro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// Just find the dollar sign
static int	find_dllsign(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			return (i);
		i += 1;
	}
	return (-1);
}

// Search for the var value
static char	*seach_var(char *var_name)
{
	int		i;
	char	*buff;

	i = find_dllsign(var_name);
	if (i != -1)
		var_name[i] = 0;
	buff = get_value(g_data.env_vars, var_name);
	if (buff == 0)
		buff = get_value(g_data.local_vars, var_name);
	if (i != -1)
		var_name[i] = '$';
	return (buff);
}

// Prepare the line
static char	*prepare(char *parsed_line, char *var_name, int k)
{
	char	*tmp;
	char	*line;
	char	*buff;

	tmp = ft_calloc(k + 1, sizeof(char));
	ft_strlcpy(tmp, parsed_line, k + 1);
	if (var_name[0] == '?')
	{
		buff = status_code();
		line = ft_strjoin(tmp, buff);
		free(buff);
		free(tmp);
		buff = ft_strjoin(line, &(var_name[1]));
		free(line);
	}
	else
	{
		buff = ft_strdup(seach_var(var_name));
		line = ft_strjoin(tmp, buff);
		free(buff);
		free(tmp);
		buff = ft_strjoin(line, &(var_name[find_dllsign(var_name)]));
		free(line);
	}
	return (buff);
}

// Expansion when mixed with string
static void	expand_mix(char **parsed_line, int k, int flag)
{
	char	*line;
	char	*var_name;

	if (k == -1 || (*parsed_line)[k] != '$')
		return ;
	var_name = &((*parsed_line)[k + 1]);
	(*parsed_line)[k] = 0;
	line = prepare(*parsed_line, var_name, k);
	free(*parsed_line);
	*parsed_line = line;
	if (flag != EXPAND_ONE)
		expand_mix(parsed_line, find_dllsign(*parsed_line), flag);
}

// This function will expand variables
// If the wildcard '*' symbol is found, expand the var first(if any)
// and then match the pattern found
void	var_expansion(char **parsed_line, int flag)
{
	int	i;
	int	k;
	int	f;

	i = 0;
	f = 0;
	if (parsed_line == 0)
		return ;
	while (parsed_line[i])
	{
		k = find_dllsign(parsed_line[i]);
		if (k != -1 && parsed_line[i][k] == '$')
		{
			expand_mix(&parsed_line[i], k, flag);
			f = flag;
		}
		if (f == EXPAND_ONE)
			break ;
		i += 1;
	}
}

	/*
		k = find_char(parsed_line[1], '*');
		if (k != -1)
			expand_wild(parsed_line[i]);
		*/