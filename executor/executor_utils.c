#include "executor.h"
#include <stdio.h>
#include <stdlib.h>
#include "builtin.h"

void free_cmd_args(char **args)
{
	int	i;

	if (!args)
		return;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

char **replace_cmd_args(t_cmd_node *cmd, t_minishell *shell_info)
{
	char	**old_args;
	char	**new_args;

	old_args = cmd->args;
	new_args = ft_argv_filter(cmd->args, shell_info->envp, &shell_info->status);
	if (!new_args)
		return (NULL);
	free_cmd_args(old_args);
	cmd->args = new_args;
	return (new_args);
} 