/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 00:17:19 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/09 00:17:48 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*find_name(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (ft_substr(str, 0, i));
}

int	expand_env(char *str, char **envp_list, t_string_builder *list)
{
	char	*env_name;
	char	*env_val;
	size_t	len;

	env_name = NULL;
	env_name = find_name(str);
	if (!env_name)
		return (0);
	env_val = search_envp(env_name, envp_list);
	if (env_val)
		append_str(list, env_val);
	len = ft_strlen(env_name);
	free(env_name);
	return (len);
}

char	*ft_advanced_substr(char *str, char **envp_list)
{
	t_string_builder	*list;

	list = builder_init();
	while (*str)
	{
		if (*str == '\'')
		{
			str++;
			while (*str && *str != '\'')
			{
				append_char(list, *str);
				str++;
			}
			if (!*str)
            {
                exec_error_handler(STDERR_FILENO, "syntax error", NULL, "unclosed quote");
                free_builder(list);
                return (NULL);
            }
            str++;
		}
		else if (*str == '"')
		{
			str++;
			while (*str && *str != '"')
			{
				if (*str == '$')
					str += expand_env(str + 1, envp_list, list);
				else
					append_char(list, *str);
				str++;
			}
			if (!*str)
            {
                exec_error_handler(STDERR_FILENO, "syntax error", NULL, "unclosed double quote");
                free_builder(list);
                return (NULL);
            }
				str++;
		}
		else if (*str == '$')
			str += expand_env(str + 1, envp_list, list) + 1;
		else
		{
			append_char(list, *str);
			str++;
		}
	}
	return (free_return_str(list));
}

char	**ft_argv_filter(char **argv, char **envp_list)
{
	char	**argv_list;
	int		i;
	int		len;

	len = ft_arglen(argv);
	i = 0;
	argv_list = malloc(sizeof(char *) * (len + 1));
	while (i < len)
	{
		argv_list[i] = ft_advanced_substr(argv[i], envp_list);
		i++;
	}
	argv_list[i] = NULL;
	return (argv_list);
}
