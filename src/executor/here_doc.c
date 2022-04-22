/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaro-d <mamaro-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:24:28 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/22 15:43:38 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	check_and_write(char *delim_with_nl, char **buff, int flag, int fd)
{
	int		len;

	len = ft_strlen(*buff);
	if (ft_strncmp(delim_with_nl, *buff, len + 1) == 0)
		return (0);
	if (flag && **buff != 0)
		expand_mix(buff, EXPAND_ALL);
	len = ft_strlen(*buff);
	write(fd, *buff, len);
	free(*buff);
	return (1);
}

static void	writing(int fd_file, char *delim, int flag)
{
	char	*buff;
	char	*delim_with_nl;

	delim_with_nl = ft_strjoin(delim, "\n");
	while (1)
	{
		write(1, "> ", 2);
		buff = get_next_line(0);
		if (buff != 0)
		{
			if (!check_and_write(delim_with_nl, &buff, flag, fd_file))
				break ;
		}
		else
		{
			write(1, "\n", 1);
			break ;
		}
		buff = 0;
	}
	if (buff)
		free(buff);
	free(delim_with_nl);
}

static int	tmp_file(int fd_file, char *delim)
{
	int	flag;

	delim = quote_resolution(delim, &flag);
	if (fd_file == -1)
		return (fd_file);
	writing(fd_file, delim, flag);
	free(delim);
	close(fd_file);
	fd_file = open("/tmp/tmp_f", O_RDONLY);
	return (fd_file);
}

int	here_doc_fd(char *delim)
{
	int	fd;

	if (delim == 0 || delim[0] == 0)
		return (-1);
	fd = tmp_file(
			open("/tmp/tmp_f", O_CREAT | O_WRONLY, 0000644), delim);
	if (fd == -1)
		write(2, "Failed to create a tmp file\n", 29);
	return (fd);
}
