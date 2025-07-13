
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
		arg = ast_new(AST_LITERAL, p->current->value);
		if (!arg)
			return (ft_lstclear(&args, ast_free_void), NULL);
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
	return (*cmd);
}

// Parse a command: simple_command redirection*
t_ast	*parse_command(t_parser *p)
{
	t_ast		*base_cmd;
	t_ast		*cmd;
	t_ast		*arg;

	cmd = parse_simple_command(p);
	if (!cmd)
		return (syntax_error_token(p->current->value));
	while (p->current && cmd)
	{
		if (!tkn_is_redirection(p->current) && !tkn_is_word(p->current))
			break ;
		handle_redirection(p, &cmd);
		if (p->current && tkn_is_word(p->current))
		{
			arg = ast_new(AST_LITERAL, p->current->value);
			if (!arg)
				return (NULL);
			base_cmd = unwrap_command(cmd);
			if (!base_cmd)
				return (syntax_error_token(p->current->value));
			add_arg_and_advance(p, &base_cmd->args, arg);
		}
	}
	return (cmd);
}
