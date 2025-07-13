/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 19:22:18 by plichota          #+#    #+#             */
/*   Updated: 2025/07/13 19:23:43 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

typedef struct	s_process_data
{
	char	*path;
	char	**envp;
	int		used_fd_in;
	int		used_fd_out;
}	t_process_data;

#endif