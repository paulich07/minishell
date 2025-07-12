/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 04:38:44 by sabruma           #+#    #+#             */
/*   Updated: 2025/07/11 03:22:49 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "minishell.h"

static char	*substitute_vars(const char *str, t_sb *sb, t_sh *sh);
static void	handle_code(t_sb *sb, t_sh *shell);
static void	handle_dollar(const char *str, size_t *i, t_sb *sb);
static void	handle_var(const char *str, size_t *i, t_sb *sb, t_sh *sh);

// Expands a single token string (e.g., "hello$USER") according to quote type
char	*expand_token(const char *str, t_quote_type quote, t_sh *shell)
{
	t_sb	*sb;
	char	*res;

	if (!str)
		return (NULL);
	if (quote == S_QUOTE)
		return (strip_if_quoted(ft_strdup(str)));
	sb = sb_create(64);
	if (!sb)
		return (NULL);
	res = substitute_vars(str, sb, shell);
	sb_free(sb);
	return (res);
}

static char	*substitute_vars(const char *str, t_sb *sb, t_sh *sh)
{
	size_t	i;
	char	*result;
	int		res_i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			res_i = str_next_c_index(str, str[i], i);
			if (res_i == -1)
				res_i = ft_strlen(str);
			while (i <= (size_t)res_i)
				sb_append_char(sb, str[i++]);
			continue ;
		}
		if (str[i] == '$' && str[i + 1])
		{
			i++;
			if (str[i] == '?')
			{
				handle_code(sb, sh);
				i++;
			}
			else if (str[i] == '_' || ft_isalpha(str[i]))
				handle_var(str, &i, sb, sh);
			else
				handle_dollar(str, &i, sb);
		}
		else
			sb_append_char(sb, str[i++]);
	}
	result = sb_build(sb);
	result = strip_if_quoted(result);
	return (result);
}

static void	handle_code(t_sb *sb, t_sh *sh)
{
	char	*val;

	val = ft_itoa(sh->last_code);
	if (val)
	{
		sb_append_str(sb, val);
		free(val);
	}
}

static void	handle_dollar(const char *str, size_t *i, t_sb *sb)
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

static void	handle_var(const char *str, size_t *i, t_sb *sb, t_sh *sh)
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
