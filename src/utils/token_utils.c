
#include "minishell.h"

void	free_token_list(t_list **list)
{
	ft_lstclear(list, free_token);
}

void	free_token(void *ptr)
{
	t_token	*token;

	token = (t_token *)ptr;
	if (token->value)
		free(token->value);
	if (token->error)
		free(token->error);
	if (token)
		free(token);
}

int	tkn_is_redirection(t_token *token)
{
	return (token->type == TKN_REDIR_IN
		|| token->type == TKN_REDIR_OUT
		|| token->type == TKN_APPEND
		|| token->type == TKN_HEREDOC);
}

int	tkn_is_word(t_token *token)
{
	return (token->type == TKN_WORD || token->type == TKN_ERROR);
}
