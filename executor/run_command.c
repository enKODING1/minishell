/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 00:17:41 by skang             #+#    #+#             */
/*   Updated: 2025/07/17 00:17:42 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	count_args(char **args)
{
	int	count;

	count = 0;
	if (!args)
		return (0);
	while (args[count])
		count++;
	return (count);
}

static int	populate_argv(char **argv, t_cmd_node *cmd_node)
{
	int	i;
	int	arg_count;

	argv[0] = ft_strdup(cmd_node->cmd);
	if (!argv[0])
		return (0);
	i = 0;
	arg_count = count_args(cmd_node->args);
	while (i < arg_count)
	{
		argv[i + 1] = ft_strdup(cmd_node->args[i]);
		if (!argv[i + 1])
		{
			free_matrix(argv);
			return (0);
		}
		i++;
	}
	argv[i + 1] = NULL;
	return (1);
}

static char	**create_argv(t_cmd_node *cmd_node)
{
	char	**argv;
	int		arg_count;

	arg_count = count_args(cmd_node->args);
	argv = (char **)calloc(arg_count + 2, sizeof(char *));
	if (!argv)
		return (NULL);
	if (populate_argv(argv, cmd_node) == 0)
	{
		return (NULL);
	}
	return (argv);
}

void	run_command(t_cmd_node *cmd_node, char *cmd_path, char **envp)
{
	char	**argv;

	argv = create_argv(cmd_node);
	if (!argv)
	{
		perror("minishell: malloc failed");
		exit(1);
	}
	if (execve(cmd_path, argv, envp) == -1)
	{
		perror("minishell: execve error");
		free_matrix(argv);
		exit(126);
	}
}
