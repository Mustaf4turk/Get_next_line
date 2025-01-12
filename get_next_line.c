/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 18:00:00 by user              #+#    #+#             */
/*   Updated: 2024/12/26 18:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*checkpoint(char *buffer)
{
	if (!buffer)
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	return (buffer);
}

int	read_to_buffer(int fd, char **buffer, char *temp)
{
	char	*new_buffer;
	int		x;

	x = read(fd, temp, BUFFER_SIZE);
	while (x > 0)
	{
		temp[x] = '\0';
		new_buffer = ft_strjoin(*buffer, temp);
		free(*buffer);
		*buffer = new_buffer;
		if (!*buffer || ft_strchr(temp, '\n'))
			break ;
		x = read(fd, temp, BUFFER_SIZE);
	}
	return (x);
}

char	*bufferload(int fd, char *buffer)
{
	char	*temp;
	int		x;

	buffer = checkpoint(buffer);
	if (!buffer)
		return (NULL);
	temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!temp)
	{
		free(buffer);
		return (NULL);
	}
	x = read_to_buffer(fd, &buffer, temp);
	free(temp);
	if (x == -1 || (x == 0 && buffer[0] == '\0'))
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

char	*trimline(char *line)
{
	char	*endline;
	int		x;

	x = 0;
	while (line[x] && line[x] != '\n')
		x++;
	endline = ft_calloc(x + 2, sizeof(char));

	if (!endline)
		return (NULL);
	x = 0;
	while (line[x] && line[x] != '\n')
	{
		endline[x] = line[x];
		x++;
	}
	if (line[x] == '\n')
		endline[x] = '\n';
	return (endline);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*line;
	char		*trimmedline;
	char		*temp;

	line = bufferload(fd, buffer);
	if (!line)
	{
		buffer = NULL;
		return (NULL);
	}
	trimmedline = trimline(line);
	temp = ft_strdup(line + ft_strlen(trimmedline));
	free(line);
	buffer = temp;
	return (trimmedline);
}
