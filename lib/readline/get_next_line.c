/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:42:20 by skang             #+#    #+#             */
/*   Updated: 2024/12/16 18:55:46 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;
	size_t	size;

	if (!s)
		return (NULL);
	if ((unsigned int)gnl_strlen(s) <= (unsigned int)start)
		return (gnl_strdup(""));
	size = gnl_strlen(s + start);
	if (size < len)
		len = size;
	sub_s = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub_s)
		return (NULL);
	gnl_strlcpy(sub_s, s + start, len + 1);
	return (sub_s);
}

static char	*gnl_strjoin(char const *s1, char const *s2)
{
	char	*join_str;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = gnl_strlen((char *)s1);
	s2_len = gnl_strlen((char *)s2);
	join_str = (char *)malloc(s1_len + s2_len + 1);
	if (join_str == NULL)
		return (NULL);
	gnl_strlcpy(join_str, (char *)s1, gnl_strlen(s1) + 1);
	gnl_strcat(join_str, (char *)s2);
	return (join_str);
}

static char	*split_stash_by_newline(char **stash)
{
	char	*result;
	char	*newline_addr;
	char	*temp_stash;
	int		newline_index;

	temp_stash = *stash;
	newline_addr = gnl_strchr(*stash, '\n');
	if (newline_addr)
	{
		newline_index = (++newline_addr) - *stash;
		result = gnl_substr(*stash, 0, newline_index);
		*stash = gnl_substr(*stash, newline_index, gnl_strlen(*stash));
	}
	else
	{
		result = gnl_strdup(*stash);
		*stash = NULL;
	}
	free(temp_stash);
	if (gnl_strlen(result) == 0 || !result)
	{
		free(result);
		return (NULL);
	}
	return (result);
}

static char	*get_read_line(int fd, char *stash, ssize_t *buffer_read)
{
	char	*buffer;
	char	*temp_stash;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	*buffer_read = read(fd, buffer, BUFFER_SIZE);
	if (*buffer_read < 0)
	{
		free(stash);
		free(buffer);
		return (NULL);
	}
	buffer[*buffer_read] = '\0';
	if (!stash)
		stash = gnl_strdup(buffer);
	else
	{
		temp_stash = stash;
		stash = gnl_strjoin(stash, buffer);
		free(temp_stash);
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	ssize_t		buffer_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer_read = 1;
	while (!gnl_strchr(stash, '\n') && buffer_read > 0)
		stash = get_read_line(fd, stash, &buffer_read);
	if (!stash || (buffer_read == 0 && gnl_strlen(stash) == 0))
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	return (split_stash_by_newline(&stash));
}