/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:55:10 by plichota          #+#    #+#             */
/*   Updated: 2025/07/14 14:55:11 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

// wrapper for project specific matrix handling
void	print_string_matrix(char **matrix)
{
	size_t	i;

	if (!matrix)
	{
		printf("(null matrix)\n");
		return ;
	}
	i = 0;
	while (matrix[i])
	{
		printf("[%zu]: \"%s\"\n", i, matrix[i]);
		i++;
	}
}
