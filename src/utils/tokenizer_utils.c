#include "minishell.h"

void	free_raw_tokens(t_list **tokens)
{
	ft_lstclear(tokens, free);
}

// is const char **p -> modify char* pointer of line but not the chars inside
char	*read_word(const char *line, const char **p)
{
	const char	*start = *p;

	while (**p && !is_whitespace(**p)
		&& !is_quote(**p) && !is_operator_char(**p))
		(*p)++;
	return (ft_substr(line, start - line, *p - start));
}

// handles also 2-char operators (>>, <<, ||, &&)
// TODO: for bonus remove the && **p != '|'
char	*read_operator(const char *line, const char **p)
{
	const char	*start = *p;

	if (is_operator_char(**p) && *(*p + 1) == **p && **p != '|')
		*p += 2;
	else
		(*p)++;
	return (ft_substr(line, start - line, *p - start));
}

//handles single and double quotes
char	*read_quoted(const char *line, const char **p, char quote)
{
	const char	*start = *p;

	(*p)++;
	while (**p && **p != quote)
		(*p)++;
	if (**p == quote)
		(*p)++;
	return (ft_substr(line, start - line, *p - start));
}
