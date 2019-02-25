/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 13:56:12 by jlagos            #+#    #+#             */
/*   Updated: 2019/01/20 14:49:04 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*fill_saved_bytes(char **saved_bytes, const int fd)
{
	char		*temp;
	char		buf[BUFF_SIZE + 1];
	int			bytes;

	if (*saved_bytes)
		*saved_bytes = NULL;
	while ((bytes = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[bytes] = '\0';
		if (!(*saved_bytes))
			*saved_bytes = ft_strnew(1);
		temp = ft_strjoin(*saved_bytes, buf);
		free(*saved_bytes);
		*saved_bytes = temp;
	}
	if (bytes == -1)
		return (NULL);
	return (*saved_bytes);
}

char		*fill_line(char **line, char **saved_bytes)
{
	int	i;

	i = 0;
	if (!**saved_bytes)
		return (NULL);
	while ((*saved_bytes)[i] != '\n' && (*saved_bytes)[i])
		i++;
	if (**saved_bytes != '\n')
	{
		*line = ft_strnew(i);
		ft_strncpy(*line, *saved_bytes, i);
		while (i && (**saved_bytes != '\n') && **saved_bytes)
		{
			i--;
			(*saved_bytes)++;
		}
	}
	return (*line);
}

int			get_next_line(const int fd, char **line)
{
	static char		*saved_bytes;
	static char		*free_bytes;
	static int		track_fd;

	if (!line || fd < 0)
		return (-1);
	if (track_fd != fd || !saved_bytes)
	{
		if (free_bytes)
			ft_strdel(&free_bytes);
		if (!(fill_saved_bytes(&saved_bytes, fd)))
			return (-1);
		free_bytes = saved_bytes;
		track_fd = fd;
	}
	if (*saved_bytes == '\n')
	{
		saved_bytes++;
		if (*saved_bytes == '\n')
			**line = '\0';
	}
	if (!(fill_line(&*line, &saved_bytes)))
		return (0);
	return (1);
}
