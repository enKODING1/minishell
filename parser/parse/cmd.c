/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <skang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:35:07 by skang          #+#    #+#             */
/*   Updated: 2025/07/16 23:06:47 by skang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdlib.h>

#define INIT_ARGC 8

static char	**ft_args_realloc(char **old, int old_cap, int new_cap)
{
	char	**new_args;
	int		j;

	j = 0;
	new_args = (char **)ft_calloc(new_cap, sizeof(char *));
	if (!new_args)
		exit(1);
	while (j < old_cap)
	{
		new_args[j] = old[j];
		j++;
	}
	free(old);
	return (new_args);
}

static void	parse_cmd_args(t_parser *parser, t_cmd_node *cmd_head, int *i,
		int *cap)
{
	int	new_cap;

	if (peek_token(parser)->type == WORD)
	{
		if (cmd_head->cmd == NULL)
			cmd_head->cmd = ft_strdup(peek_token(parser)->value);
		else
		{
			if (*i + 2 >= *cap)
			{
				new_cap = (*cap) * 2;
				cmd_head->args = ft_args_realloc(cmd_head->args, *cap, new_cap);
				*cap = new_cap;
			}
			cmd_head->args[(*i)++] = ft_strdup(peek_token(parser)->value);
			cmd_head->args[*i] = NULL;
		}
		consume_token(parser);
	}
}

static int	parse_cmd_redirs(t_parser *parser, t_cmd_node *cmd_head)
{
	t_redir	*redir;
	t_redir	*current;

	redir = parse_redirs(parser);
	if (parser->has_error)
		return (0);
	if (!cmd_head->redirs)
	{
		cmd_head->redirs = redir;
	}
	else
	{
		current = cmd_head->redirs;
		while (current->next)
			current = current->next;
		current->next = redir;
	}
	return (1);
}

static t_cmd_node	*init_cmd_node(int *cap)
{
	t_cmd_node	*cmd_head;

	cmd_head = (t_cmd_node *)ft_calloc(1, sizeof(t_cmd_node));
	if (!cmd_head)
		exit(1);
	cmd_head->type = NODE_CMD;
	*cap = INIT_ARGC;
	cmd_head->args = (char **)ft_calloc(*cap, sizeof(char *));
	if (!cmd_head->args)
		exit(1);
	return (cmd_head);
}

t_node	*parse_cmd(t_parser *parser)
{
	t_cmd_node	*cmd_head;
	int			cap;
	int			i;

	cmd_head = init_cmd_node(&cap);
	i = 0;
	while (peek_token(parser) && peek_token(parser)->type != PIPE
		&& peek_token(parser)->type != END)
	{
		if (peek_token(parser)->type == WORD)
			parse_cmd_args(parser, cmd_head, &i, &cap);
		else if (peek_token(parser)->type >= HEREDOC
			&& peek_token(parser)->type <= IN)
		{
			if (!parse_cmd_redirs(parser, cmd_head))
			{
				free_cmd_node(cmd_head);
				return (NULL);
			}
		}
		else
			break ;
	}
	cmd_head->args[i] = NULL;
	return ((t_node *)cmd_head);
}
