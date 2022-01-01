/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 01:11:55 by asimoes           #+#    #+#             */
/*   Updated: 2021/05/26 15:48:57 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	extract_line(t_fd_data *data, char **line)
{
	char	*endl;
	char	*old_data;

	if (data->buffer == NULL)
		return (-1);
	endl = gnl_strchr(data->buffer, '\n');
	if (endl != NULL)
	{
		*line = gnl_strncpy(NULL, data->buffer, endl - data->buffer);
		if (!(*line))
			return (-2);
		old_data = data->buffer;
		data->buffer = gnl_strncpy(NULL, endl + 1, gnl_strlen(endl + 1));
		free(old_data);
		return (1);
	}
	if (data->eof == 1)
	{
		*line = gnl_strncpy(NULL, data->buffer, gnl_strlen(data->buffer));
		free(data->buffer);
		data->buffer = NULL;
		data->eof = 0;
		return (0);
	}
	return (-1);
}

char	*copy_buffer(char *dest, char *src, int len, short int *error)
{
	char	*old_data;

	old_data = dest;
	dest = gnl_strjoin(dest, src, len);
	if (!dest)
		*error = 1;
	free(old_data);
	return (dest);
}

int	read_fd(int fd, t_fd_data *data)
{
	char	*readbuf;
	int		len;
	short	error;

	error = 0;
	readbuf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!readbuf)
		return (-1);
	len = read(fd, readbuf, BUFFER_SIZE);
	while (len >= 0)
	{
		readbuf[len] = 0;
		data->buffer = copy_buffer(data->buffer, readbuf, len, &error);
		if (gnl_strchr(data->buffer, '\n') != NULL || error != 0 || len == 0)
			break ;
		len = read(fd, readbuf, BUFFER_SIZE);
	}
	free(readbuf);
	if (error == 1 || len < 0)
		return (-1);
	if (len == 0)
		data->eof = 1;
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static t_fd_data	data;
	int					ret;

	if (fd < 0 || line == NULL)
		return (-1);
	ret = extract_line(&data, line);
	if (ret != -1)
		return (ret);
	ret = read_fd(fd, &data);
	if (ret == -1)
	{
		free(data.buffer);
		return (ret);
	}
	return (extract_line(&data, line));
}
