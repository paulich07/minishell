/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_is_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:50:13 by sabruma           #+#    #+#             */
/*   Updated: 2025/07/10 17:04:10 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	command_valid(t_ast *node)
{
	if (node->type != AST_COMMAND)
		return (1);
	if (!node->argv && !node->argv[0])
	{
		node->error = ft_strdup("newline");
		return (0);
	}
	return (1);
}

int	literal_valid(t_ast *node)
{
	if (node->type != AST_LITERAL)
		return (1);
	if (!node->value)
	{
		node->error = ft_strdup("newline");
		return (0);
	}
	return (1);
}

int	pipe_valid(t_ast *node)
{
	if (node->type != AST_PIPE)
		return (1);
	if (!node->left)
	{
		node->error = ft_strdup("|");
		return (0);
	}
	if (!node->right)
	{
		node->error = ft_strdup("newline");
		return (0);
	}
	if (!ast_is_valid(node->left) || !ast_is_valid(node->right))
		return (0);
	return (1);
}

int	redirection_valid(t_ast *node)
{
	if (!ast_is_redirection(node))
		return (1);
	if (!node->right)
	{
		node->error = ft_strdup("newline");
		return (0);
	}
	if (node->right->type != AST_LITERAL || !node->right->value)
	{
		node->error = ft_strdup("newline");
		return (0);
	}
	if (node->left && !ast_is_valid(node->left))
		return (0);
	return (1);
}

int	ast_is_valid(t_ast *node)
{
	int	result;

	if (!node || ast_has_error(node))
		return (0);
	result = 1;
	result = result && command_valid(node);
	result = result && literal_valid(node);
	result = result && pipe_valid(node);
	result = result && redirection_valid(node);
	return (result);
}
