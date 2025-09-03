/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cm_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:42:20 by skang             #+#    #+#             */
/*   Updated: 2025/07/17 00:11:15 by skang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cm_readline.h"

static char	*cm_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;
	size_t	size;

	if (!s)
		return (NULL);
	if ((unsigned int)cm_strlen(s) <= (unsigned int)start)
		return (cm_strdup(""));
	size = cm_strlen(s + start);
	if (size < len)
		len = size;
	sub_s = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub_s)
		return (NULL);
	cm_strlcpy(sub_s, s + start, len + 1);
	return (sub_s);
}

static char	*cm_strjoin(char const *s1, char const *s2)
{
	char	*join_str;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = cm_strlen((char *)s1);
	s2_len = cm_strlen((char *)s2);
	join_str = (char *)malloc(s1_len + s2_len + 1);
	if (join_str == NULL)
		return (NULL);
	cm_strlcpy(join_str, (char *)s1, cm_strlen(s1) + 1);
	cm_strcat(join_str, (char *)s2);
	return (join_str);
}

static char	*split_stash_by_newline(char **stash)
{
	char	*result;
	char	*newline_addr;
	char	*temp_stash;
	int		newline_index;

	temp_stash = *stash;
	newline_addr = cm_strchr(*stash, '\n');
	if (newline_addr)
	{
		newline_index = (++newline_addr) - *stash;
		result = cm_substr(*stash, 0, newline_index);
		*stash = cm_substr(*stash, newline_index, cm_strlen(*stash));
	}
	else
	{
		result = cm_strdup(*stash);
		*stash = NULL;
	}
	free(temp_stash);
	if (cm_strlen(result) == 0 || !result)
	{
		free(result);
		return (NULL);
	}
	return (result);
}

static char	*cm_read_line(int fd, char *stash, ssize_t *buffer_read)
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
		stash = cm_strdup(buffer);
	else
	{
		temp_stash = stash;
		stash = cm_strjoin(stash, buffer);
		free(temp_stash);
	}
	free(buffer);
	return (stash);
}

char	*cm_readline(int fd)
{
	static char	*stash;
	ssize_t		buffer_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer_read = 1;
	while (!cm_strchr(stash, '\n') && buffer_read > 0)
		stash = cm_read_line(fd, stash, &buffer_read);
	if (!stash || (buffer_read == 0 && cm_strlen(stash) == 0))
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	return (split_stash_by_newline(&stash));
}
