/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:28:31 by plichota          #+#    #+#             */
/*   Updated: 2025/07/12 20:57:35 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_status = 0;

// handle Ctrl-C in heredoc (exit heredoc)
// close STDIN for breaking the while loop of heredoc
void	handler_sigint_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		g_signal_status = EXIT_SIGINT;
		close(STDIN_FILENO);
	}
}

// handle Ctrl-C (break line)
void	handler_sigaction(int sig)
{
	if (sig == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_signal_status = 128 + SIGINT;
	}
}

// handle Ctrl-C (SIGINT) and Ctrl-\ (SIGQUIT)
// use SA_RESTART to resume syscalls (readline) instead of failing
void	init_signals()
{
	struct sigaction	sa;

	sa.sa_handler = handler_sigaction;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	// signal(SIGQUIT, SIG_IGN); // to do levare prima di pushare
}

void print_newline(int sig)
{
	(void)	sig;
	write(STDERR_FILENO, "\n", 1);
}

void	ignore_signals()
{
	signal(SIGINT, print_newline);
	signal(SIGQUIT, SIG_IGN);
}

void	set_default_signals()
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
