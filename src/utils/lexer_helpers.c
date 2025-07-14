/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:09:50 by sabruma           #+#    #+#             */
/*   Updated: 2025/07/09 17:06:25 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// 1 if errors, 0 otherwise
int	check_for_errors(t_token *token)
{
	const char	*error_prefix;

	if (token->type != TKN_ERROR)
		return (0);
	if (token->value[0] == '\'')
		error_prefix = "Unclosed single quote: ";
	else if (token->value[0] == '"')
		error_prefix = "Unclosed double quote: ";
	else
		error_prefix = "Unknown token: ";
	token->error = ft_strjoin(error_prefix, token->value);
	return (token->error != NULL);
}
