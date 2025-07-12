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
#include "minishell.h"

int	should_join_to_last(const char *line, char *start)
{
	return (line != start && !is_whitespace(*(start -1))
		&& !is_operator_char(*(start - 1)));
}

int	insert_node(t_list **tokens, const char *line, char *start, char *word)
{
	t_list	*node;

	node = ft_lstlast(tokens);
	if (should_join_to_last(line, start) && node != NULL)
	{
		node->content = ft_strfreejoin(node->content, word);
		if (!node->content)
			return (0);
		return (1);
	}
	node = ft_lstnew(word);
	if (!node)
		return (0);
	ft_lstadd_back(&tokens, node);
	return (1);
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
		str_skip_spaces(&p);
		if (*p == '\0')
			break ;
		start = (char *)p;
		word = read_next_token(line, &p);
		if (!word)
			return (free_raw_tokens(&tokens), NULL);
		if (!insert_node(&tokens, line, start, word))
			return (free_raw_tokens(&tokens), free(word), NULL);
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
