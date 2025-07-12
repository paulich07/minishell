/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:30:30 by plichota          #+#    #+#             */
/*   Updated: 2025/07/12 21:28:22 by plichota         ###   ########.fr       */
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

int	heredoc_loop(char *delim, int fd_out, t_sh *shell)
{
	char *line;
	char *expanded_line;

	g_last_signal = 0;
	while (1)
	{
		line = readline("heredoc> ");
		if (g_last_signal == SIGINT)
		{
			g_last_signal = 0;
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
	int fd[2];
	int saved_stdin;
	int status;
	struct sigaction	old_sa;
	struct sigaction	new_sa;
	
	if (!ast || !ast->right)
		return (-1);
	// save old struct
	if (sigaction(SIGINT, NULL, &old_sa) == -1)
		return (perror("sigaction get"), -1);
	// dup stdin
	saved_stdin = dup(STDIN_FILENO); // --------------------- close saved_stdin
	if (saved_stdin == -1)
		return (perror("dup stdin"), -1);
	// init new struct
	sigemptyset(&new_sa.sa_mask);
	new_sa.sa_handler = handler_sigint_heredoc;
	new_sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &new_sa, NULL) == -1) // ---------- revert struct
		return (perror("sigaction set"), close(saved_stdin), -1);
	// create pipe ------------------------------------------ close fds
	if (pipe(fd) == -1)
	{
		sigaction(SIGINT, &old_sa, NULL); // to do reset and exit f
		close(saved_stdin);
		return (perror("pipe"), -1);
	}
	// loop
	status = heredoc_loop(ast->right->value, fd[1], shell);
	// Restore
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	close(fd[1]);
	sigaction(SIGINT, &old_sa, NULL);
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
