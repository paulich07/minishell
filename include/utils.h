/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:54:35 by plichota          #+#    #+#             */
/*   Updated: 2025/07/14 15:02:57 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

int			str_next_c_index(const char *str, int c, int start);
char		*strip_if_quoted(char *value);
int			str_contains_quote(const char *str);

#endif