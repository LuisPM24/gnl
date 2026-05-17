/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupalomi <lupalomi@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 13:29:35 by lupalomi          #+#    #+#             */
/*   Updated: 2026/05/17 13:29:36 by lupalomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	next_line(char **buffer, int len)
{
	char	*new_buffer;

	new_buffer = ft_strdup(*buffer + len);
	if (!new_buffer)
	{
		free(*buffer);
		*buffer = NULL;
		return ;
	}
	free(*buffer);
	*buffer = new_buffer;
}

static char	*get_text(char **buffer)
{
	int		cont;
	int		len;
	char	*line;

	len = 0;
	cont = 0;
	if (!*buffer || !**buffer)
		return (NULL);
	while ((*buffer)[len] && (*buffer)[len] != '\n')
		len++;
	line = (char *)malloc((len + 2) * sizeof(char));
	if (!line)
		return (NULL);
	while (cont < len)
	{
		line[cont] = (*buffer)[cont];
		cont++;
	}
	if ((*buffer)[len] == '\n')
		line[len++] = '\n';
	line[len] = '\0';
	next_line(buffer, len);
	return (line);
}

static char	*gnl_process(int fd, char *bf_read)
{
	int			bytes_read;
	static char	*buffer[FOPEN_MAX];
	char		*aux;

	if (!buffer[fd])
		buffer[fd] = ft_strdup("");
	bytes_read = 1;
	while (bytes_read > 0)
	{
		if (!buffer[fd] || ft_strchr(buffer[fd], '\n'))
			break ;
		bytes_read = read(fd, bf_read, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer[fd]), buffer[fd] = NULL, NULL);
		bf_read[bytes_read] = '\0';
		aux = ft_strjoin(buffer[fd], bf_read);
		free(buffer[fd]);
		buffer[fd] = aux;
		if (!buffer[fd])
			return (NULL);
	}
	if (!buffer[fd] || *buffer[fd] == '\0')
		return (free(buffer[fd]), buffer[fd] = NULL, NULL);
	return (get_text(&buffer[fd]));
}

char	*get_next_line(int fd)
{
	char	*bf_read;
	char	*ret;

	if (fd < 0 || fd >= FOPEN_MAX || BUFFER_SIZE <= 0
		|| BUFFER_SIZE > INT_MAX)
		return (NULL);
	bf_read = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!bf_read)
		return (NULL);
	ret = gnl_process(fd, bf_read);
	free(bf_read);
	return (ret);
}
