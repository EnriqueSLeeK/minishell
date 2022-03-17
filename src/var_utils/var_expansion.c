/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 13:44:03 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/16 21:16:52 by ensebast         ###   ########.fr       */
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

void	var_expansion(char **parsed_line, int flag)
{
	int		i;
	int		k;

	i = 0;
	while (parsed_line[i])
	{
		k = find_dllsign(parsed_line[i]);
		if (k != -1 && parsed_line[i][k] == '$')
		{
			expand_mix(&parsed_line[i], k, flag);
			if (flag == EXPAND_ONE)
				break ;
		}
		i += 1;
	}
}
