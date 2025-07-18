/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:03:16 by sabruma           #+#    #+#             */
/*   Updated: 2025/07/13 22:32:08 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// $var -> $var value
// Core expansion entry point
void	expand_ast(t_ast *root, t_sh *shell)
{
	if (!root)
		return ;
	astt_post_ctx(root, should_expand_token, shell);
}

void	should_expand_token(t_ast *node, void *ctx)
{
	t_sh	*shell;

	shell = (t_sh *)ctx;
	if (!node)
		return ;
	if (!node->no_expand_self)
	{
		if (node->type == AST_COMMAND)
			expand_command_args(node, shell);
		else if (node->value && node->quote != S_QUOTE)
			expand_token_value(node, shell);
	}
	if (node->value)
		strip_if_quoted(node->value);
}

// Handles heredoc input, expands lines only if delimiter is unquoted
char	*read_heredoc(const char *delimiter, t_quote_type quote, t_sh *shell)
{
	t_list	*lines;
	char	*line;
	char	*exp;
	char	*res;

	lines = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, delimiter))
			break ;
		if (quote == N_QUOTE)
		{
			exp = expand_token(line, N_QUOTE, shell);
			free(line);
			line = exp;
		}
		ft_lstadd_back(&lines, ft_lstnew(line));
	}
	res = lst_join(lines);
	ft_lstclear(&lines, free);
	return (res);
}
