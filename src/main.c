/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:51:36 by plichota          #+#    #+#             */
/*   Updated: 2025/07/12 22:41:10 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	was_ctrl_c_pressed(t_sh *shell)
{
	if (shell->last_code == 130)
	{
		write(2, "\n", 1);
		free(shell->line);
		shell->line = NULL;
		return (1);
	}
	return (0);
}

int	str_is_only_spaces(const char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
	{
		if (!is_whitespace(str[i]))
			return (0);
	}
	return (1);
}

// exit_heredoc_sigint into last status?
void	main_loop(t_sh *shell)
{
	int		status;

	while (1)
	{
		shell->line = readline("> ");
		update_signal_status(shell);
		if (was_ctrl_c_pressed(shell))
			continue ;
		if (!shell->line)
			break ;
		if (!str_is_only_spaces(shell->line))
			add_history(shell->line);
		shell->tree = read_command_line(shell->line);
		expand_ast(shell->tree, shell);
		if (!shell->tree)
			continue ;
		status = preprocess_redirections(shell->tree, shell);
		if (status < 0)
			ast_free(shell->tree);
		else
			shell->last_code = executor(shell->tree, 0, 1, shell, 0, 0);
		free(shell->line);
	}
}

// It handles Ctrl+D with if (!line) break;
int	main(int argc, char *argv[], char *envp[])
{
	t_sh	shell;

	(void) argv;
	shell = (t_sh){0};
	init_shell(&shell, envp);
	init_signals();
	if (argc != 1)
		return (perror("Wrong number of arguments"), 0);
	main_loop(&shell);
	rl_clear_history();
	free_all(&shell);
	printf("exit\n");
	return (0);
}
