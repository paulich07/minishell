/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:51:36 by plichota          #+#    #+#             */
/*   Updated: 2025/07/12 22:25:44 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	remove_quotes(char *value, int quote_idx)
{
	int			len;
	int			next;

	if (!value)
		return (-1);
	len = ft_strlen(value);
	if (!is_quote(value[quote_idx]))
		return (quote_idx);
	next = str_next_c_index(value, value[quote_idx], quote_idx);
	if (next == -1)
		return (-1);
	ft_memmove(value + quote_idx, value + quote_idx + 1, next - quote_idx - 1);
	ft_memmove(value + next - 1, value + next + 1, len - next);
	value[len - 2] = '\0';
	return (next - 1);
}

int	str_next_c_index(const char *str, int c, int start)
{
	int	i;

	i = start - 1;
	while (str && str[++i])
	{
		if (str[i] == c && i > start)
			return (i);
	}
	return (-1);
}

/**
 * Strips quotes from a string if they are quoted
 * Returns the stripped string
 */
char	*strip_if_quoted(char *value)
{
	int	i;

	i = 0;
	while (value && value[i])
	{
		if (is_quote(value[i]))
		{
			i = remove_quotes(value, i);
			if (i == -1)
				return (free(value), NULL);
		}
		else
			i++;
	}
	return (value);
}

void	str_skip_spaces(const char **str)
{
	while (str && **str && is_whitespace(**str))
		(*str)++;
}
