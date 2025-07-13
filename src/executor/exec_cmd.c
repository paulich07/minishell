/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:17:05 by plichota          #+#    #+#             */
/*   Updated: 2025/07/13 21:53:38 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_child(t_ast *ast, t_sh *shell)
{
	set_default_signals();
	if (is_builtin(ast))
		exit(execute_builtin(ast, shell));
	execute_command(ast, shell);
}

// crea e gestisce il fork
int	spawn_command(t_ast *ast, t_sh *shell)
{
	pid_t	pid;
	int		status;

	if (!ast || !ast->argv || !ast->argv[0] || !shell)
		return (1);
	if (is_builtin(ast) && !shell->process.is_in_pipeline)
		return (execute_builtin(ast, shell));
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
		handle_child(ast, shell);
	ignore_signals();
	if (waitpid(pid, &status, 0) == -1)
		return (perror("waitpid failed"), 1);
	init_signals();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else
		return (1);
}

// execute command with execve 
int	execute_command(t_ast *ast, t_sh *shell)
{
	if (!ast || !ast->argv || !ast->argv[0])
		cleanup_and_exit(shell, 0);
	init_process_data(ast, shell);
	if (!shell->process.path || !shell->process.envp)
		cleanup_and_exit(shell, EXIT_CMD_NOT_FOUND);
	if (!check_command_access(shell->process.path))
		cleanup_and_exit(shell, EXIT_PERMISSION_DENIED);
	execve(shell->process.path, ast->argv, shell->process.envp);
	cleanup_and_exit(shell, EXIT_PERMISSION_DENIED);
	return (1);
}
