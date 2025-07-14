/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 04:40:05 by sabruma           #+#    #+#             */
/*   Updated: 2025/07/09 19:34:57 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// Parse a pipeline: command '|' command
t_ast	*parse_pipeline(t_parser *p)
{
	t_ast		*right;
	t_ast		*left;

	if (!p->current || p->current->type == TKN_PIPE)
		return (syntax_error_token("|"));
	left = parse_command(p);
	if (!left)
		return (syntax_error_token("|"));
	while (p->current && p->current->type == TKN_PIPE)
	{
		advance(p);
		if (!p->current)
			return (ast_free(left), syntax_error_token("|"));
		right = parse_command(p);
		if (!right)
			return (ast_free(left), syntax_error_token("|"));
		left = ast_binary_op(AST_PIPE, "|", left, right);
	}
	return (left);
}

// driver: checks if there's some errors propagated from the lexer
t_ast	*parse(t_list *lexemes)
{
	t_parser	parser;
	t_list		*tmp;
	t_token		*token;

	tmp = lexemes;
	while (tmp)
	{
		token = (t_token *)tmp->content;
		if (token->type == TKN_ERROR)
		{
			if (token->error)
				return (ast_error(token->error));
			else
				return (ast_error("syntax error"));
		}
		tmp = tmp->next;
	}
	parser.tokens = lexemes;
	if (lexemes)
		parser.current = (t_token *)lexemes->content;
	else
		parser.current = NULL;
	return (parse_pipeline(&parser));
}
