#include "parser.h"
#include <stdio.h>


t_token_node * create_token_list(t_lexer *lexer)
{
    t_token_type *tok;
    t_token_node *tok_head;
    t_token_node *tok_node;
    
    // add 잘되는지 확인하기
    while(tok->type != END)
    {
        tok = lexer->next_token(lexer);
        tok_node = create_token_node(tok);
        add_token_node(&tok_head, tok_node);
    }
     
    t_token_node *head = tok_head;
    while(head)
    {
        head = head->next;
        printf("type[%s], val[%s]\n", token_type_str(head->next->token->type), head->next->token->value);
    }
    
    return tok_head;
}

t_token_node *create_token_node(t_token_type *tok)
{
    t_token_node *tok_node = (t_token_node *)malloc(sizeof(t_token_node));
    if (!tok_node)
        return NULL;
       
    tok_node->token = tok;
    tok_node->next = NULL;

    return tok_node;
}

int add_token_node(t_token_node **head, t_token_node *tok)
{
    t_token_node *tok_node;

    if((*head)->next == NULL)
    {
       (*head)->next = tok; 
        return 0 ;
    }

    tok_node = (*head);   
    while(tok_node)
        tok_node = tok_node->next;

    tok_node->next = tok;
    return 1;
}