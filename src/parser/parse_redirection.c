
#include "minishell.h"
#include "parser.h"

static t_ast	*init_f_node(t_parser *p)
{
	char	*filename;
	t_ast	*f_node;

	filename = ft_strdup(p->current->value);
	if (!filename)
		return (NULL);
	f_node = ast_new(AST_LITERAL, filename, 0);
	if (f_node)
		f_node->quote = p->current->quote;
	free(filename);
	return (f_node);
}

// Helper to parse a single redirection and return the updated command node
t_ast	*parse_redirection(t_parser *p, t_ast *cmd)
{
	char	*op;
	t_ast	*f_node;
	t_ast	*r_node;
	t_token	*redir;

	redir = p->current;
	advance(p);
	if (!p->current)
		return (ast_free(cmd), syntax_error_token("newline"));
	if (!tkn_is_word(p->current))
		return (ast_free(cmd), syntax_error_token(p->current->value));
	op = ft_strdup(redir->value);
	f_node = init_f_node(p);
	if (!f_node)
		return (free(op), ast_free(cmd), syntax_error_token(redir->value));
	advance(p);
	if (!f_node || !tkn_is_redirection(redir))
		return (free(op), ast_free(cmd), ast_free(f_node),
			syntax_error_token(redir->value));
	r_node = ast_binary_op((t_ast_type)redir->type, op, astdup(cmd), f_node);
	ast_free(cmd);
	free(op);
	if (!r_node)
		return (ast_free(f_node), syntax_error_token(p->current->value));
	return (r_node);
}
