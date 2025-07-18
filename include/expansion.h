/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:03:43 by sabruma           #+#    #+#             */
/*   Updated: 2025/07/14 16:50:47 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(EXPANSION_H)
# define EXPANSION_H

# include "matrix.h"
# include "list.h"
# include "ast.h"
# include "env.h"

// Core expansion entry point
void	expand_ast(t_ast *root, t_sh *shell);

// operation for each node
void	should_expand_token(t_ast *node, void *ctx);

// Expands a command node's arguments and fills argv/argc
void	expand_command_args(t_ast *cmd, t_sh *shell);
void	split_command_args(t_list **exp, char *exp_str);

// Expands any other token->value field (except commands)
void	expand_token_value(t_ast *token, t_sh *shell);

// Expands a single token string (e.g., "hello$USER") according to quote type
char	*expand_token(const char *str, t_quote_type quote, t_sh *shell);

// Handles heredoc input, expands lines only if delimiter is unquoted
char	*read_heredoc(const char *delimiter, t_quote_type quote, t_sh *shell);
char	*lst_join(t_list *lst);

void	_expand_last_code(t_sb *sb, t_sh *sh);
void	_expand_skip_squotes(const char *str, t_sb *sb, size_t *i);

#endif // EXPANSION_H
