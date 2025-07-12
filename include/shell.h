/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:03:29 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 20:05:26 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "list.h"
# include "ast.h"

typedef struct s_sh
{
	// list of t_env
	t_list	*env;
	// for $?
	int		last_code;
	// set if running interactively
	int		is_interactive;
	// current AST
	t_ast	*tree;
	// current readline line
	char	*line;
}	t_sh;

#endif