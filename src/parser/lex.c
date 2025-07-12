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

#include "parser.h"

static t_token	*init_token(t_list *raw_tokens);

// early returns are all malloc-related
t_list	*lex(t_list *raw_tokens)
{
	t_list	*lexemes;
	t_token	*token;
	t_list	*new_node;

	lexemes = NULL;
	while (raw_tokens)
	{
		token = init_token(raw_tokens);
		if (!token)
			return (free_token_list(&lexemes), NULL);
		new_node = ft_lstnew(token);
		if (!new_node)
			return (free_token(token), free_token_list(&lexemes), NULL);
		ft_lstadd_back(&lexemes, new_node);
		raw_tokens = raw_tokens->next;
	}
	return (lexemes);
}

static t_token	*init_token(t_list *raw_tokens)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->error = NULL;
	token->value = ft_strdup((char *)raw_tokens->content);
	if (!token->value)
		return (free(token), NULL);
	token->type = classify_token(token->value);
	token->quote = classify_quote(token->value);
	if (!strip_if_quoted(token))
		return (free_token(token), NULL);
	check_for_errors(token);
	return (token);
}

int	remove_quotes(t_token *token, int quote_idx)
{
	int			len;
	int			next;

	if (!token->value)
		return (-1);
	len = ft_strlen(token->value);
	if (!is_quote(token->value[quote_idx]))
		return (0);
	next = str_next_c_index(token->value, token->value[quote_idx],
			quote_idx + 1);
	if (next == -1)
		return (-1);
	ft_memmove(token->value + quote_idx,
		token->value + quote_idx + 1, next - quote_idx - 1);
	ft_memmove(token->value + next - 1,
		token->value + next + 1, len - next);
	token->value[len - 2] = '\0';
	return (next - 2);
}

// 1 if stripped, 0 otherwise
int	strip_if_quoted(t_token *token)
{
	int	i;

	i = -1;
	while (token->value && token->value[++i])
	{
		if (is_quote(token->value[i]))
		{
			if (token->value[i] == '\'')
			{
				i = str_next_c_index(token->value, token->value[i], i);
				if (i == -1)
					return (0);
				continue ;
			}
			i = remove_quotes(token, i);
			if (i == -1)
				return (0);
			i = i - 1;
		}
	}
	return (1);
}
