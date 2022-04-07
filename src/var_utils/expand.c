/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:29:43 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/07 16:29:48 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*contructor(char *buff, char *tmp)
{
	char	*var_with_sufix;

	var_with_sufix = 0;
	if (buff != 0 && tmp != 0)
	{
		var_with_sufix = ft_strjoin(buff, tmp);
		free(tmp);
		if (var_with_sufix == 0)
			return (0);
	}
	else if (buff == 0 && tmp != 0)
		var_with_sufix = tmp;
	return (var_with_sufix);
}

// Search for the var value
static char	*seach_var(char *var_name)
{
	int		i;
	int		k;
	char	*tmp;
	char	*buff;

	i = find_char(var_name, '$');
	if (i != -1)
		var_name[i] = 0;
	tmp = 0;
	k = check_varname(var_name);
	if (k != -1)
	{
		tmp = ft_strdup(&(var_name[k]));
		var_name[k] = 0;
	}
	buff = get_value(g_data.env_vars, var_name);
	if (buff == 0)
		buff = get_value(g_data.local_vars, var_name);
	if (i != -1)
		var_name[i] = '$';
	if (k != -1)
		return (contructor(buff, tmp));
	return (ft_strdup(buff));
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
		buff = seach_var(var_name);
		line = ft_strjoin(tmp, buff);
		free(buff);
		free(tmp);
		buff = ft_strjoin(line, &(var_name[find_char(var_name, '$')]));
		free(line);
	}
	return (buff);
}

// Expansion when mixed with string
void	expand_mix(char **parsed_line, int k, int flag)
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
		expand_mix(parsed_line, find_char(*parsed_line, '$'), flag);
}
