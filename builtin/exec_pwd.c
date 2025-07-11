/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:12:01 by jinwpark          #+#    #+#             */
/*   Updated: 2025/07/11 23:29:39 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	echo_pwd(char *str, int fd)
{
	char	*tmp;

	tmp = ft_substr(str, 4, ft_strlen(str));
	ft_putstr_fd(tmp, fd);
	ft_putstr_fd("\n", fd);
	free(tmp);
}

char	*option_check(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i][0] == '-')
			return (ft_substr(argv[i], 0, 1));
		i++;
	}
	return (NULL);
}

void	exec_pwd(char **argv, char **envp_list)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	if (option_check(argv))
	{
		str = option_check(argv);
		exec_error_handler(STDERR_FILENO, "pwd", str, " BAD OPTION");
		free(str);
		return ;
	}
	while (envp_list[i])
	{
		if (ft_strncmp("PWD=", envp_list[i], 4) == 0)
			str = envp_list[i];
		i++;
	}
	if (!str)
		exec_error_handler(STDERR_FILENO, "pwd", NULL, " HOME NOT SET");
	else
		echo_pwd(str, STDOUT_FILENO);
}
