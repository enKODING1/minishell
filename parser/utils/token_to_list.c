/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:57:09 by skang             #+#    #+#             */
/*   Updated: 2025/07/16 23:14:14 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_token_list(t_token_node *head)
{
	t_token_node	*current;

	current = head;
	printf("--- Token List ---\n");
	while (current)
	{
		printf("type[%s], val[%s]\n", token_type_str(current->token->type),
			current->token->value);
		current = current->next;
	}
	printf("------------------\n");
}

t_token_node	*create_token_list(t_lexer *lexer)
{
	t_token_type	*tok;
	t_token_node	*tok_head;
	t_token_node	*tok_node;

	tok_head = NULL;
	while (1)
	{
		tok = lexer->next_token(lexer);
		if (tok->type == END)
		{
			free_token(tok);
			break ;
		}
		tok_node = create_token_node(tok);
		if (!tok_node)
		{
			free_token(tok);
			free_token_list(tok_head);
			return (NULL);
		}
		add_token_node(&tok_head, tok_node);
	}
	return (tok_head);
}

t_token_node	*create_token_node(t_token_type *tok)
{
	t_token_node	*tok_node;

	tok_node = (t_token_node *)malloc(sizeof(t_token_node));
	if (!tok_node)
		return (NULL);
	tok_node->token = tok;
	tok_node->next = NULL;
	return (tok_node);
}

int	add_token_node(t_token_node **head, t_token_node *new_node)
{
	t_token_node	*current;

	if (!head || !new_node)
		return (-1);
	if (*head == NULL)
	{
		*head = new_node;
		return (0);
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
	return (1);
}
