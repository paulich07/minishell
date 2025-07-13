/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:28:31 by plichota          #+#    #+#             */
/*   Updated: 2025/07/13 12:41:30 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_last_signal = 0;

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

void	init_heredoc_signals()
{
	struct sigaction	sa;

	sa.sa_handler = handler_sigint_heredoc;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	// signal(SIGQUIT, SIG_IGN); // to do levare prima di pushare
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
