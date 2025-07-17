/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 23:50:56 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/17 19:14:26 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	find_key_and_copy(char *key, char **envp_list, char **tmp_list)
{
	int		i;
	int		found_idx;
	char	*old_key;

	i = 0;
	found_idx = -1;
	while (envp_list[i])
	{
		old_key = ft_find_key(envp_list[i]);
		if (ft_strcmp(key, old_key) == 0)
			found_idx = i;
		tmp_list[i] = ft_strdup(envp_list[i]);
		if (!tmp_list[i])
		{
			while (i > 0)
				free(tmp_list[--i]);
			free(old_key);
			return (-2);
		}
		free(old_key);
		i++;
	}
	return (found_idx);
}

int	update_or_add_entry(int j, char **tmp_list, char *update_arg,
		int list_len)
{
	if (j != -1)
	{
		free(tmp_list[j]);
		tmp_list[j] = ft_strdup(update_arg);
		if (!tmp_list[j])
			return (-1);
		tmp_list[list_len] = NULL;
	}
	else
	{
		tmp_list[list_len] = ft_strdup(update_arg);
		if (!tmp_list[list_len])
			return (-1);
		tmp_list[list_len + 1] = NULL;
	}
	return (0);
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && (str1[i] == str2[i]))
		i++;
	return (str1[i] - str2[i]);
}

char	**cleanup_and_fail(char **list, char *key, char *value)
{
	free_envp(list);
	free(key);
	free(value);
	return (NULL);
}
