/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 22:20:28 by tpassin           #+#    #+#             */
/*   Updated: 2024/05/23 19:17:27 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*line_buffer(int fd, char *next_read, char *buf, int *b);
static char	*set_line(char *line_buffer);
static char	*extract_line(char *buf, char *t, int *b);

char	*get_next_line(int fd, int *b)
{
	static char	*next_read = NULL;
	char		*line;
	char		*buf;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (free(next_read), NULL);
	line = line_buffer(fd, next_read, buf, b);
	if (b == 0)
		return (free(next_read), NULL);
	free(buf);
	buf = NULL;
	if (!line)
		return (free(line), NULL);
	next_read = set_line(line);
	buf = line;
	if (buf == NULL)
		return (free(buf), free(next_read), NULL);
	if (!next_read)
	{
		free(next_read);
		next_read = NULL;
	}
	line = extract_line(buf, next_read, b);
	return (line);
}

static char	*line_buffer(int fd, char *next_read, char *buf, int *b)
{
	ssize_t	b_read;
	char	*tmp;

	b_read = BUFFER_SIZE;
	while (b_read > 0)
	{
		b_read = read(fd, buf, BUFFER_SIZE);
		if (b_read == -1)
		{
			*b = 0;
			return (free(next_read), NULL);
		}
		if (b_read == 0)
			break ;
		buf[b_read] = '\0';
		if (!next_read)
			next_read = ft_strdup("");
		tmp = next_read;
		next_read = ft_join(tmp, buf);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (next_read);
}

static char	*set_line(char *line_buffer)
{
	char	*stash;
	ssize_t	i;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == 0)
		return (NULL);
	stash = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (stash && stash[0] == 0)
		return (free(stash), NULL);
	line_buffer[i + 1] = '\0';
	return (stash);
}

static char	*extract_line(char *buf, char *t, int *b)
{
	ssize_t	i;
	char	*new_line;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	new_line = malloc(sizeof(char) * (i + 2));
	if (new_line == NULL)
	{
		*b = 0;
		return (free(buf), free(t), NULL);
	}
	i = -1;
	while (buf[++i] && buf[i] != '\n')
		new_line[i] = buf[i];
	if (buf[i] == '\n')
	{
		new_line[i] = buf[i];
		i++;
	}
	new_line[i] = '\0';
	free(buf);
	return (new_line);
}
