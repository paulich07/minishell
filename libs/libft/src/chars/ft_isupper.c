/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:11:51 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 20:11:52 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isupper(int c);

int	ft_isupper(int c)
{
	if (c >= 0x41 && c <= 0x5A)
		return (c);
	return (0);
}
