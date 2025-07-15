/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 00:17:19 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/15 06:12:57 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*find_name(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '?')
		return (ft_substr(str, 0, 1));
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (ft_substr(str, 0, i));
}

int	expand_env(char *str, char **envp_list, t_string_builder *list, int *status)
{
	char	*env_name;
	char	*env_val;
	size_t	len;

	env_name = NULL;
	env_name = find_name(str);
	if (!env_name)
		return (0);
	if (ft_strcmp(env_name, "?") == 0)
		env_val = ft_itoa(*status);
	else
		env_val = search_envp(env_name, envp_list);
	if (env_val)
		append_str(list, env_val);
	len = ft_strlen(env_name);
	free(env_name);
	free(env_val);
	return (len);
}

char	*ft_advanced_substr(char *str, char **envp_list, int *status)
{
	t_string_builder	*list;
	int					error_check;

	list = builder_init();
	error_check = 0;
	while (*str && !error_check)
	{
		if (*str == '\'')
			error_check = handle_single_quote(&str, list, status);
		else if (*str == '"')
			error_check = handle_double_quote(&str, envp_list, list, status);
		else if (*str == '$')
			str += expand_env(str + 1, envp_list, list, status) + 1;
		else
		{
			append_char(list, *str);
			str++;
		}
	}
	if (error_check)
	{
		free_builder(list);
		return (NULL);
	}
	return (free_return_str(list));
}

char	**ft_argv_filter(char **argv, char **envp_list, int *status)
{
	char	**argv_list;
	int		i;
	int		len;

	len = ft_arglen(argv);
	i = 0;
	argv_list = malloc(sizeof(char *) * (len + 1));
	while (i < len)
	{
		argv_list[i] = ft_advanced_substr(argv[i], envp_list, status);
		i++;
	}
	argv_list[i] = NULL;
	return (argv_list);
}
