/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:17:05 by plichota          #+#    #+#             */
/*   Updated: 2025/07/13 19:26:25 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// crea e gestisce il fork
int spawn_command(t_ast *ast, int fd_in, int fd_out, t_sh *shell, int is_in_pipeline)
{
	pid_t pid;
	int status;

	if (!ast || !ast->argv || !ast->argv[0] || !shell)
		return (1);
	if (is_builtin(ast) && !is_in_pipeline)
		return (execute_builtin(ast, fd_in, fd_out, shell));
	pid = fork();
	if (pid < 0)
		return (1); // to do gestire errore
	if (pid == 0)
	{
		set_default_signals();
		if (is_builtin(ast))
			exit(execute_builtin(ast, fd_in, fd_out, shell));
		execute_command(ast, fd_in, fd_out, shell); // esce da solo
	}
	// ferma il waitpid del padre assoluto
	// if (!is_last_child(ast))
	// 	return (-1);
	ignore_signals();
	// to do spostare dopo l'esecuzione di tutti i comandi 
	// aspetta tutti i figli forkati (da solo si da' -1 quando i figli sono finiti)
	// while (waitpid(-1, &status, 0) != -1) per l'ultimo figlio
	if (waitpid(pid, &status, 0) == -1) { // gestisco pid inesistente, zombie e processi gia' terminati
		perror("waitpid failed");
		return (1);
	}
	init_signals();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else
		return (1); // to do gestire errore
}

// execute command with execve 
int	execute_command(t_ast *ast, int fd_in, int fd_out, t_sh *shell)
{
	t_process_data	process = (t_process_data){0};

	process.used_fd_in = fd_in;
	process.used_fd_out = fd_out;
	if (!ast || !ast->argv || !ast->argv[0])
		cleanup_and_exit(&process, shell, 0);
	init_process_data(ast, &process, shell);
	if (!process.path || !process.envp)
		cleanup_and_exit(&process, shell, EXIT_CMD_NOT_FOUND);
	if (!check_command_access(process.path))
		cleanup_and_exit(&process, shell, EXIT_PERMISSION_DENIED);
	execve(process.path, ast->argv, process.envp);
	cleanup_and_exit(&process, shell, EXIT_PERMISSION_DENIED);
	return (1);
}
