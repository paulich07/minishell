/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:07:48 by plichota          #+#    #+#             */
/*   Updated: 2025/07/13 19:22:59 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "ast.h"
# include "shell.h"
# include "process.h"

// execute command
int		execute_command(t_ast *ast, int fd_in, int fd_out, t_sh *shell);
int		spawn_command(t_ast *ast, int fd_in, int fd_out, t_sh *shell, int is_in_pipeline);

// execute command utils
int		check_command_access(char *path);
char	*search_path(char *cmd, t_sh *shell);
char	*find_command_path(char *cmd, char **paths);
void	init_process_data(t_ast *ast, t_process_data *process, t_sh *shell);

// execute pipeline
int		execute_pipeline(t_ast *ast, int fd_in, int fd_out, t_sh *shell, int is_fork);

// execute operator
// int		execute_operator(t_ast *ast, int fd_in, int fd_out, t_sh *shell);

// execute builtin
int		execute_builtin(t_ast *ast, int fd_in, int fd_out, t_sh *shell);

// core
int		executor(t_ast *ast, int fd_in, int fd_out, t_sh *shell, int is_fork, int is_in_pipeline);
int		is_builtin(t_ast *ast);

#endif
