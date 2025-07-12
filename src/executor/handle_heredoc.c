/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:30:30 by plichota          #+#    #+#             */
/*   Updated: 2025/07/12 23:02:59 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *expand_variables(char *line, t_sh *shell)
{
	if (!line)
		return (NULL);
	// per ora assumo che non ci siano quotes
	return (expand_token(line, N_QUOTE, shell));
}

int heredoc_loop(char *delim, int fd_out, t_sh *shell)
{
	char *line;
	char *expanded_line;

	g_last_signal = 0;
	while (1)
	{
		line = readline("heredoc> ");
		update_signal_status(shell);
		if (shell->last_code != 0)
		{
			write(2, "\n", 1);
			return (free(line), EXIT_SIGINT);
		}
		if (!line || strcmp(line, delim) == 0)
			break ;
		expanded_line = expand_variables(line, shell);
		if (!expanded_line)
			return (free(line), -1);
		write(fd_out, expanded_line, ft_strlen(expanded_line));
		write(fd_out, "\n", 1);
		free(expanded_line);
	}
	return (0);
}

// handles heredoc with the buffer of the pipe instead of a temp file
// uses close(STDIN_FILENO) for exiting the loop with Ctrl-C
// and then resets it
int	handle_heredoc(t_ast *ast, t_sh *shell)
{
	int		fd[2];
	int		saved_stdin;
	int		status;

	if (!ast || !ast->right)
		return (-1);
	// dup stdin
	saved_stdin = dup(STDIN_FILENO); // --------------------- close saved_stdin
	if (saved_stdin == -1)
		return (perror("dup stdin"), -1);
	init_hereodc_signals();
	// create pipe ------------------------------------------ close fds
	if (pipe(fd) == -1)
	{
		init_signals();
		close(saved_stdin);
		return (perror("pipe"), -1);
	}
	// loop
	status = heredoc_loop(ast->right->value, fd[1], shell);
	// Restore
	restore_state(saved_stdin, STDIN_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	close(fd[1]);
	init_signals();
	// (if ctrl-c) update status and close the entire pipe
	if (status == EXIT_SIGINT)
	{
		shell->last_code = EXIT_SIGINT;
		g_last_signal = 0;
		return (close(fd[0]), EXIT_HEREDOC_SIGINT);
	}
	// otherwise the read enpoint remains open
	return (fd[0]);
}
