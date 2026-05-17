/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupalomi <lupalomi@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 09:37:19 by lupalomi          #+#    #+#             */
/*   Updated: 2026/05/17 09:37:21 by lupalomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	next_line(char	**buffer, int len)
{
	char	*new_buffer;

	new_buffer = ft_strdup(*buffer + len);
	if (!new_buffer)
		return ;
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
	static char	*buffer;
	char		*aux;

	if (!buffer)
		buffer = ft_strdup("");
	bytes_read = 1;
	while (bytes_read > 0)
	{
		if (!buffer || ft_strchr(buffer, '\n'))
			break ;
		bytes_read = read(fd, bf_read, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), buffer = NULL, NULL);
		bf_read[bytes_read] = '\0';
		aux = ft_strjoin(buffer, bf_read);
		free(buffer);
		buffer = aux;
	}
	if (!buffer || *buffer == '\0')
		return (free(buffer), buffer = NULL, NULL);
	return (get_text(&buffer));
}

char	*get_next_line(int fd)
{
	char	*bf_read;
	char	*ret;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	bf_read = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!bf_read)
		return (NULL);
	ret = gnl_process(fd, bf_read);
	return (free(bf_read), ret);
}
