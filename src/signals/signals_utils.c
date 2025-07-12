/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:28:31 by plichota          #+#    #+#             */
/*   Updated: 2025/07/12 21:42:12 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_newline(int sig)
{
	(void)	sig;
	write(STDERR_FILENO, "\n", 1);
}

void update_signal_status(t_sh *shell)
{
	if (!shell)
		return ;
	shell->last_code = 128 + g_last_signal;
	g_last_signal = 0;
}
