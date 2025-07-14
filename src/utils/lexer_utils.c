/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:55:36 by plichota          #+#    #+#             */
/*   Updated: 2025/07/14 14:55:37 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// add strncmp of && and || if gonna do bonus :──)
t_token_type	classify_token(const char *raw_token)
{
	size_t	len;

	if (!raw_token)
		return (TKN_WORD);
	len = ft_strlen(raw_token);
	if (len == 2 && ft_strncmp(raw_token, ">>", 2) == 0)
		return (TKN_APPEND);
	if (len == 2 && ft_strncmp(raw_token, "<<", 2) == 0)
		return (TKN_HEREDOC);
	if (len == 1 && raw_token[0] == '|')
		return (TKN_PIPE);
	if (len == 1 && raw_token[0] == '>')
		return (TKN_REDIR_OUT);
	if (len == 1 && raw_token[0] == '<')
		return (TKN_REDIR_IN);
	if (is_malformed(raw_token, len))
		return (TKN_ERROR);
	return (TKN_WORD);
}

t_quote_type	classify_quote(const char *raw_token)
{
	size_t	len;

	len = ft_strlen(raw_token);
	if (len >= 2 && is_quoted(raw_token, len, '\''))
		return (S_QUOTE);
	if (len >= 2 && is_quoted(raw_token, len, '"'))
		return (D_QUOTE);
	if (raw_token && (ft_strchr(raw_token, '\'')
			|| ft_strchr(raw_token, '"')))
		return (W_QUOTE);
	return (N_QUOTE);
}

int	is_quoted(const char *raw_token, int len, char quote)
{
	return (raw_token[0] == quote && raw_token[len - 1] == quote);
}

int	is_malformed(const char *raw_token, int len)
{
	int		next_idx;
	int		i;

	i = -1;
	while (++i < len)
	{
		if (is_quote(raw_token[i]))
		{
			next_idx = str_next_c_index(raw_token, raw_token[i], i);
			if (next_idx == -1)
				return (1);
			i = next_idx;
		}
	}
	return (0);
}
