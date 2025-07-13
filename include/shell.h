/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:03:29 by sabruma           #+#    #+#             */
/*   Updated: 2025/07/13 20:13:15 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "list.h"
# include "ast.h"
# include "process.h"

typedef struct s_sh
{
	// list of t_env
	t_list			*env;
	// for $?
	int				last_code;
	// set if running interactively
	int				is_interactive;
	// current AST
	t_ast			*tree;
	// current readline line
	char			*line;
	// dup stdio
	int				fd_stdin;
	int				fd_stdout;
	// current process data
	t_process_data	process;
}	t_sh;

#endif