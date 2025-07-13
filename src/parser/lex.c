/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:12:12 by sabruma           #+#    #+#             */
/*   Updated: 2025/07/09 16:56:18 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static t_token	*init_token(t_list *raw_tokens, t_token_type prev_type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->error = NULL;
	token->value = ft_strdup((char *)raw_tokens->content);
	if (!token->value)
		return (free(token), NULL);
	token->type = classify_token(token->value);
	if (prev_type == TKN_HEREDOC && token->type == TKN_WORD)
		token->is_heredoc_word = 1;
	token->quote = classify_quote(token->value);
	if (!token->value)
		return (free_token(token), NULL);
	check_for_errors(token);
	return (token);
}

// early returns are all malloc-related
t_list	*lex(t_list *raw_tokens)
{
	t_list			*lexemes;
	t_token			*token;
	t_list			*new_node;
	t_token_type	prev_type;

	lexemes = NULL;
	prev_type = TKN_WORD;
	while (raw_tokens)
	{
		token = init_token(raw_tokens, prev_type);
		if (!token)
			return (free_token_list(&lexemes), NULL);
		new_node = ft_lstnew(token);
		if (!new_node)
			return (free_token(token), free_token_list(&lexemes), NULL);
		ft_lstadd_back(&lexemes, new_node);
		prev_type = token->type;
		raw_tokens = raw_tokens->next;
	}
	return (lexemes);
}
