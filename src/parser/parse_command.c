
#include "minishell.h"
#include "parser.h"

static void	add_arg_and_advance(t_parser *p, t_list **args, t_ast *arg)
{
	arg->quote = p->current->quote;
	ft_lstadd_back(args, ft_lstnew(arg));
	advance(p);
}

// Parse a simple command: WORD+
t_ast	*parse_simple_command(t_parser *p)
{
	t_ast	*cmd;
	t_ast	*arg;
	t_list	*args;

	if (!p->current)
		return (syntax_error_token("newline"));
	args = NULL;
	while (p->current && tkn_is_word(p->current))
	{
		arg = ast_new(AST_LITERAL, p->current->value,
				p->current->is_heredoc_word, 0);
		if (!arg)
			return (ft_lstclear(&args, ast_free_void), NULL);
		if (str_contains_quote(p->current->value))
			arg->no_expand_content = 1;
		add_arg_and_advance(p, &args, arg);
	}
	cmd = ast_cmd(args);
	return (cmd);
}

static t_ast	*handle_redirection(t_parser *p, t_ast **cmd)
{
	if (tkn_is_redirection(p->current))
	{
		*cmd = parse_redirection(p, *cmd);
		if (!*cmd)
			return (syntax_error_token(p->current->value));
	}
	return (NULL);
}

static t_ast	*handle_word(t_parser *p, t_ast **cmd)
{
	t_ast		*arg;
	t_ast		*base_cmd;

	if (!p->current || !tkn_is_word(p->current))
		return (*cmd);
	arg = ast_new(AST_LITERAL, p->current->value,
			p->current->is_heredoc_word, 0);
	if (!arg)
		return (syntax_error_token(p->current->value));
	if (str_contains_quote(p->current->value))
		arg->no_expand_content = 1;
	base_cmd = unwrap_command(*cmd);
	if (!base_cmd)
		return (syntax_error_token(p->current->value));
	add_arg_and_advance(p, &base_cmd->args, arg);
	return (NULL);
}

// Parse a command: simple_command redirection*
t_ast	*parse_command(t_parser *p)
{
	t_ast		*cmd;
	t_ast		*error;

	cmd = parse_simple_command(p);
	if (!cmd)
		return (syntax_error_token(p->current->value));
	while (p->current && cmd)
	{
		if (!tkn_is_redirection(p->current) && !tkn_is_word(p->current))
			break ;
		error = handle_redirection(p, &cmd);
		if (!error)
			error = handle_word(p, &cmd);
		if (error)
			return (error);
	}
	return (cmd);
}
