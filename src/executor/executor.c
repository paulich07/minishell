/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:17:05 by plichota          #+#    #+#             */
/*   Updated: 2025/07/12 21:45:45 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_ast *ast)
{
	const char *cmd;

	if (!ast || !ast->argv || !ast->argv[0])
		return (0);
	cmd = ast->argv[0];
	return (
		ft_strcmp(cmd, "echo") == 0 ||
		ft_strcmp(cmd, "cd") == 0 ||
		ft_strcmp(cmd, "pwd") == 0 ||
		ft_strcmp(cmd, "export") == 0 ||
		ft_strcmp(cmd, "unset") == 0 ||
		ft_strcmp(cmd, "env") == 0 ||
		ft_strcmp(cmd, "exit") == 0
	);
}

int	executor(t_ast *ast, int fd_in, int fd_out, t_sh *shell, int is_fork, int is_in_pipeline)
{
	int status;

	status = 127;
	if (!ast || !shell)
		return (status);
	// print_ast(ast, 1);
	if (ast_is_redirection(ast))
		return (executor(ast->left, fd_in, fd_out, shell, is_fork, is_in_pipeline));
	if (ast_is_simple_pipeline(ast) || ast->type == AST_PIPE)
		status = execute_pipeline(ast, fd_in, fd_out, shell, is_fork);
	else if (ast_is_command(ast))
	{
		if (is_fork) // uso il padre per eseguire direttamente
		{
			if (is_builtin(ast))
				status = execute_builtin(ast, fd_in, fd_out, shell);
			else
				status = execute_command(ast, fd_in, fd_out, shell);
		}
		else // processo principale: forki ed esegui cmd o esegui direttamente builtin
			status = spawn_command(ast, fd_in, fd_out, shell, is_in_pipeline);
	}
	else
		return (0);
	update_signal_status(shell);
	if (!is_fork) // prendere solo status ultimo figlio (non forkato)
		shell->last_code = status;
	return (shell->last_code);
}
