/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 04:38:44 by sabruma           #+#    #+#             */
/*   Updated: 2025/07/14 16:55:33 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_expand_variable(const char *str, size_t *i, t_sb *sb, t_sh *sh)
{
	size_t	start;
	char	*key;
	char	*val;

	start = (*i)++;
	while (str[*i] && ft_isalnum(str[*i]))
		(*i)++;
	key = ft_substr(str, start, *i - start);
	val = get_env_value(sh->env, key);
	free(key);
	if (val)
		sb_append_str(sb, val);
}

void	_expand_dollar(const char *str, size_t *i, t_sb *sb)
{
	int		next_quote;

	sb_append_char(sb, '$');
	if (is_quote(str[*i]))
	{
		next_quote = str_next_c_index(str, str[*i], *i);
		if (next_quote == -1)
			next_quote = ft_strlen(str);
		while (*i <= (size_t)next_quote)
			sb_append_char(sb, str[(*i)++]);
	}
	else
		sb_append_char(sb, str[*i]);
	(*i)++;
}

void	_expand_handle_dollar(const char *str, t_sb *sb, t_sh *sh, size_t *i)
{
	(*i)++;
	if (str[*i] == '?')
	{
		_expand_last_code(sb, sh);
		(*i)++;
	}
	else if (str[*i] == '_' || ft_isalpha(str[*i]))
		_expand_variable(str, i, sb, sh);
	else
		_expand_dollar(str, i, sb);
}

static char	*_expand_token_loop(const char *str, t_sb *sb, t_sh *sh)
{
	size_t	i;
	int		quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (is_quote(str[i]) && quote == 0)
			quote = str[i];
		else if (quote == str[i] && quote != 0)
			quote = 0;
		if (str[i] == '\'' && quote != '"')
		{
			_expand_skip_squotes(str, sb, &i);
			continue ;
		}
		if (str[i] == '$' && str[i + 1])
			_expand_handle_dollar(str, sb, sh, &i);
		else
			sb_append_char(sb, str[i++]);
	}
	return (sb_build(sb));
}

// Expands a single token string (e.g., "hello$USER") according to quote type
char	*expand_token(const char *str, t_quote_type quote, t_sh *shell)
{
	t_sb	*sb;
	char	*res;

	if (!str)
		return (NULL);
	if (quote == S_QUOTE)
		return (ft_strdup(str));
	sb = sb_create(64);
	if (!sb)
		return (NULL);
	res = _expand_token_loop(str, sb, shell);
	sb_free(sb);
	return (res);
}
