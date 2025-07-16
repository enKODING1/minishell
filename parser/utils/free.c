/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 23:14:00 by skang             #+#    #+#             */
/*   Updated: 2025/07/16 23:14:02 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_token_list(t_token_node *head)
{
	t_token_node	*ptr;

	if (!head)
		return ;
	ptr = head;
	while (ptr)
	{
		head = ptr->next;
		free_token(ptr->token);
		free(ptr);
		ptr = head;
	}
}

void	free_redir_list(t_redir *redir)
{
	t_redir	*current;
	t_redir	*next;

	if (!redir)
		return ;
	current = redir;
	while (current)
	{
		next = current->next;
		if (current->filename)
			free(current->filename);
		free(current);
		current = next;
	}
}

void	free_cmd_node(t_cmd_node *cmd_node)
{
	int	i;

	if (!cmd_node)
		return ;
	if (cmd_node->cmd)
	{
		free(cmd_node->cmd);
	}
	if (cmd_node->args)
	{
		i = 0;
		while (cmd_node->args[i])
		{
			free(cmd_node->args[i]);
			i++;
		}
		free(cmd_node->args);
	}
	if (cmd_node->redirs)
		free_redir_list(cmd_node->redirs);
	free(cmd_node);
}
