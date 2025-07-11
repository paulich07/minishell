/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_is_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:37:40 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/23 13:44:10 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int	ast_is_command(const t_ast *node)
{
	return (node && node->type == AST_COMMAND);
}
