#include "parser.h"

void print_ast(t_node *node, int indent)
{
	if (!node) return;
	for (int i = 0; i < indent; i++) printf("  ");

	if (node->type == NODE_PIPE)
	{
		t_pipe_node *pipe_node = (t_pipe_node *)node;
		printf("PIPE\n");
		print_ast(pipe_node->left, indent + 1);
		print_ast(pipe_node->right, indent + 1);
	}
	else if (node->type == NODE_CMD)
	{
		t_cmd_node *cmd_node = (t_cmd_node *)node;
		printf("CMD: [%s]\n", cmd_node->cmd ? cmd_node->cmd : "NULL");
		
		for (int i = 0; cmd_node->args[i]; i++)
		{
			for (int j = 0; j < indent + 1; j++) printf("  ");
			printf("ARG: %s\n", cmd_node->args[i]);
		}
		
		t_redir *r = cmd_node->redirs;
		while(r)
		{
			for (int j = 0; j < indent + 1; j++) printf("  ");
			printf("REDIR: %s %s\n", token_type_str(r->type), r->filename);
			r = r->next;
		}
	}
}