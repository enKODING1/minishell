/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 21:12:49 by skang             #+#    #+#             */
/*   Updated: 2025/02/27 21:05:13 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	word_count(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	**free_all(char **result, int idx)
{
	int	i;

	i = 0;
	while (i < idx)
		free(result[i++]);
	free(result);
	return (NULL);
}

static char	*get_next_word(const char *s, char c, size_t *pos)
{
	size_t	start;
	size_t	end;

	while (s[*pos] == c)
		(*pos)++;
	start = *pos;
	while (s[*pos] && s[*pos] != c)
		(*pos)++;
	end = *pos;
	return (ft_substr(s, start, end - start));
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	pos;
	int		words;
	int		i;

	if (!s)
		return (NULL);
	words = word_count(s, c);
	result = (char **)malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	i = 0;
	pos = 0;
	while (i < words)
	{
		result[i] = get_next_word(s, c, &pos);
		if (!result[i])
			return (free_all(result, i));
		i++;
	}
	result[words] = NULL;
	return (result);
}
