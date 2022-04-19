/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:00:47 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/19 17:42:10 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	check(int *mode, char c);
int		search_expandable_var(char *line);

char	*contructor(char *buff, char *tmp)
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
char	*seach_var(char *var_name)
{
	int		k;
	char	*tmp;
	char	*buff;

	k = check_varname(var_name);
	if (k != -1)
	{
		tmp = ft_strdup(&(var_name[k]));
		var_name[k] = 0;
	}
	buff = get_value(g_data.env_vars, var_name);
	if (buff == 0)
		buff = get_value(g_data.local_vars, var_name);
	if (k != -1)
		return (contructor(buff, tmp));
	return (ft_strdup(buff));
}

// Prepare the line
char	*prepare(char *parsed_line, char *var_name, int k)
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
		buff = ft_strjoin(line, &(var_name[search_expandable_var(var_name)]));
		free(line);
	}
	return (buff);
}
