
#include "minishell.h"

int	is_operator_char(char c)
{
	return (c == '|' || c == '&' || c == '<' || c == '>');
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}
