/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_replace_subtree.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:46:12 by sabruma           #+#    #+#             */
/*   Updated: 2025/07/14 16:28:04 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	ast_replace_subtree(t_ast **target, t_ast *replace)
{
	if (!target || *target == replace)
		return;
	ast_free(*target);
	*target = replace;
}
