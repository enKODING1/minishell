
#include "get_next_line.h"

size_t	gnl_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	index;

	index = 0;
	if (n > 0)
	{
		while (index < n - 1 && src[index] != '\0')
		{
			dest[index] = src[index];
			index++;
		}
		dest[index] = '\0';
	}
	return (gnl_strlen(src));
}

size_t	gnl_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (*s++)
		count++;
	return (count);
}

char	*gnl_strcat(char *dest, char *src)
{
	int	index;
	int	dest_len;

	dest_len = 0;
	index = 0;
	while (dest[dest_len])
		dest_len++;
	while (src[index] != '\0')
	{
		dest[dest_len + index] = src[index];
		index++;
	}
	dest[dest_len + index] = '\0';
	return (dest);
}

char	*gnl_strdup(const char *s)
{
	char	*dup_s;
	size_t	s_len;
	size_t	index;

	s_len = gnl_strlen(s);
	dup_s = (char *)malloc(sizeof(char) * (s_len + 1));
	if (dup_s == NULL)
		return (NULL);
	index = 0;
	while (index < s_len)
	{
		dup_s[index] = s[index];
		index++;
	}
	dup_s[index] = '\0';
	return (dup_s);
}

char	*gnl_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (*s == c)
		return ((char *)s);
	return (NULL);
}