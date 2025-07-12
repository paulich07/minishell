/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:35:28 by sabruma           #+#    #+#             */
/*   Updated: 2025/07/09 16:13:24 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*ft_strfreejoin(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

// Creates tokens out of the command line
// separated by spaces or operators
// saves them into a t_list* of char*
t_list	*tokenize(const char *line)
{
	t_list		*tokens;
	t_list		*node;
	char		*word;
	const char	*p = line;
	char		*start;

	if (!line)
		return (NULL);
	tokens = NULL;
	while (*p)
	{
		while (is_whitespace(*p))
			p++;
		if (*p == '\0')
			break ;
		start = (char *)p;
		word = read_next_token(line, &p);
		if (!word)
			return (free_raw_tokens(&tokens), NULL);
		node = ft_lstlast(tokens);
		if (line != start && !is_whitespace(*(start -1)) && !is_operator_char(*(start - 1)) && node != NULL)
		{
			node->content = ft_strfreejoin(node->content, word);
			if (!node->content)
				return (free_raw_tokens(&tokens), NULL);
			continue ;
		}
		node = ft_lstnew(word);
		if (!node)
			return (free(word), free_raw_tokens(&tokens), NULL);
		ft_lstadd_back(&tokens, node);
	}
	return (tokens);
}

char	*read_next_token(const char *line, const char **p)
{
	if (is_quote(**p)) 
		return (read_quoted(line, p, **p));
	else if (is_operator_char(**p))
		return (read_operator(line, p));
	else
		return (read_word(line, p));
}

void	free_raw_tokens(t_list **tokens)
{
	ft_lstclear(tokens, free);
}
