/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:48:28 by plichota          #+#    #+#             */
/*   Updated: 2025/07/14 16:49:58 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_expand_last_code(t_sb *sb, t_sh *sh)
{
	char	*val;

	val = ft_itoa(sh->last_code);
	if (val)
	{
		sb_append_str(sb, val);
		free(val);
	}
}

void	_expand_skip_squotes(const char *str, t_sb *sb, size_t *i)
{
	int		res_i;

	res_i = str_next_c_index(str, str[*i], *i);
	if (res_i == -1)
		res_i = ft_strlen(str);
	while (*i <= (size_t)res_i)
		sb_append_char(sb, str[(*i)++]);
}
