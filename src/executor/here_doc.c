/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:24:28 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/04 16:33:09 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	writing(int fd_file, char *delim)
{
	int		len;
	char	*buff;

	while (1)
	{
		buff = get_next_line(0);
		if (buff != 0)
		{
			len = ft_strlen(buff);
			if (ft_strncmp(delim, buff, len + 1) == -10)
				break ;
			write(fd_file, buff, len);
		}
		else
			break ;
		free(buff);
		buff = 0;
	}
	if (buff)
		free(buff);
}

static int	tmp_file(int fd_file, char *delim)
{

	if (fd_file == -1)
		return (fd_file);
	writing(fd_file, delim);
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
	unlink("/tmp/tmp_f");
	return (fd);
}
