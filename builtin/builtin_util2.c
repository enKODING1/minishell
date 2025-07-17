/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_util2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 23:53:54 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/17 16:47:01 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_arglen(char **argv)
{
	int	i;

	i = 0;
	if (argv[0] == NULL)
		return (0);
	while (argv[i] != NULL)
		i++;
	return (i);
}

void	two_free(char *str1, char *str2)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
}

char	**get_envp_list(char **envp_list)
{
	char	**tmp_list;
	int		i;

	i = 0;
	tmp_list = malloc(sizeof(char *) * (ft_arglen(envp_list) + 1));
	if (!tmp_list)
		return (NULL);
	while (envp_list[i])
	{
		tmp_list[i] = ft_strdup(envp_list[i]);
		if (!tmp_list[i])
		{
			while (i > 0)
				free(tmp_list[--i]);
			free(tmp_list);
			return (NULL);
		}
		i++;
	}
	tmp_list[i] = NULL;
	return (tmp_list);
}

char	*remove_quote(char *str)
{
	int		position;
	int		current_position;
	char	quote;

	position = 0;
	current_position = -1;
	quote = str[0];
	if (!(quote == '\"' || quote == '\''))
		return (str);
	while (str[position])
	{
		if (str[position] == quote)
			current_position = position;
		else if (str[position] == '\0')
			break ;
		position++;
	}
	if (current_position == -1)
		return (str);
	return (ft_substr(str, 1, current_position - 1));
}
