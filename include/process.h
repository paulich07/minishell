/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 19:22:18 by plichota          #+#    #+#             */
/*   Updated: 2025/07/13 20:13:41 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

typedef struct s_process_data
{
	char	*path;
	char	**envp;
	int		used_fd_in;
	int		used_fd_out;
	int		is_in_pipeline;
	int		is_fork;
}	t_process_data;

void	process_init(t_process_data *process);

#endif