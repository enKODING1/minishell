/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 23:33:32 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/11 23:33:35 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_key_value(char *arg, char **key, char **value)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(arg);
	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	*key = ft_substr(arg, 0, i);
	i++;
	*value = ft_substr(arg, i, len);
}

char	*make_value(char *key, char *value)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*complete_str;

	tmp1 = ft_strjoin("\"", value);
	tmp2 = ft_strjoin(tmp1, "\"");
	tmp3 = ft_strjoin(key, "=");
	complete_str = ft_strjoin(tmp3, tmp2);
	free(tmp1);
	free(tmp2);
	free(tmp3);
	return (complete_str);
}

char	*ft_update(char *arg)
{
	char	*key;
	char	*value;
	char	*update_str;

	ft_key_value(arg, &key, &value);
	if (value == NULL || value[0] == '\0')
		update_str = ft_strjoin(key, "=\"\"");
	else
		update_str = make_value(key, value);
	free(value);
	free(key);
	return (update_str);
}

char	*ft_find_key(char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (ft_substr(arg, 0, i));
}
