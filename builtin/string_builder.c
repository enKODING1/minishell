/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 00:17:57 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/09 00:45:39 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_string_builder	*builder_init(void)
{
	t_string_builder	*sb;

	sb = malloc(sizeof(t_string_builder));
	if (!sb)
		return (NULL);
	sb->cap = 16;
	sb->str = malloc(sizeof(char) * sb->cap);
	if (!sb->str)
	{
		free(sb);
		return (NULL);
	}
	sb->str[0] = '\0';
	sb->len = 0;
	return (sb);
}

void	append_char(t_string_builder *sb, char c)
{
	size_t	new_cap;
	char	*str;

	if (sb->len + 1 >= sb->cap)
	{
		new_cap = sb->cap * 2;
		str = malloc(sizeof(char) * new_cap);
		ft_memcpy(str, sb->str, sb->len);
		free(sb->str);
		sb->str = str;
		sb->cap = new_cap;
	}
	sb->str[sb->len] = c;
	sb->len++;
	sb->str[sb->len] = '\0';
}

void	append_str(t_string_builder *sb, char *str)
{
	while (*str)
	{
		append_char(sb, *str);
		str++;
	}
}

char	*free_return_str(t_string_builder *sb)
{
	char	*str;

	if (!sb)
		return (NULL);
	str = ft_strdup(sb->str);
	free(sb->str);
	free(sb);
	return (str);
}

void	free_builder(t_string_builder *sb)
{
	free(sb->str);
	free(sb);
}
