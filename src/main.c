/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:51:36 by plichota          #+#    #+#             */
/*   Updated: 2025/07/12 22:24:11 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_loop(t_sh *shell)
{
	int		status;
	char	*line;
	t_ast	*tree;

	while (1)
	{
		line = readline("> ");
		update_signal_status(shell);
		if (shell->last_code != 0)
		{
			write(2, "\n", 1);
			free(line);
			continue;
		}
		if (!line)
			break ;
		if (ft_strlen(line) > 0)
			add_history(line);
		tree = read_command_line(line);
		expand_ast(tree, shell);
		if (!tree)
		{
			// perror("Generic parser error");
			continue ;
		}
		status = preprocess_redirections(tree, shell);
		if (status < 0)
		{
			// exit_heredoc_sigint into last status?
			ast_free(tree);
		} else {
			shell->last_code = executor(tree, STDIN_FILENO, STDOUT_FILENO, shell, 0, 0); // restituisce status code
		}
		free(line);
	}
}

// It handles Ctrl+D with if (!line) break;
int	main(int argc, char *argv[], char *envp[])
{
	t_sh	shell;

	(void) argv;
	init_shell(&shell, envp);
	init_signals();
	if (argc != 1)
		return (perror("Wrong number of arguments"), 0);
	main_loop(&shell);
	rl_clear_history();
	free_all(&shell);
	printf("exit\n"); // TO DO tenere o togliere?
	return (0);
}
