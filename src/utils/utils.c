/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:22:58 by plichota          #+#    #+#             */
/*   Updated: 2025/07/11 03:49:53 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_sh *shell, char *envp[])
{
	shell->env = envp_to_env(envp);
	shell->last_code = 0;
	shell->is_interactive = isatty(STDIN_FILENO);
}

t_ast	*read_command_line(const char *line)
{
	t_list	*raw;
	t_list	*lexed;
	t_ast	*tree;

	raw = tokenize(line);
	if (!raw)
		return (NULL);
	lexed = lex(raw);
	if (!lexed)
		return (NULL);
	tree = parse(lexed);
	if (!tree)
		return (NULL);
	if (ast_has_error(tree) && tree && tree->error)
		printf("❌ Parse error: %s\n", tree->error);
	free_raw_tokens(&raw);
	free_token_list(&lexed);
	return (tree);
}

void	cleanup_and_exit(char *path, char **envp, int exit_code, char *err_msg)
{
	if (err_msg)
		perror(err_msg);
	free(path);
	mtxfree_str(envp);
	exit(exit_code);
}


void	free_all(t_sh *shell)
{
	if (shell && shell->env)
		free_env(shell->env);
	ast_free(shell->tree);
	if (shell->line)
		free(shell->line);
	shell->tree = NULL;
	shell->line = NULL;
	shell->env = NULL;
}

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
