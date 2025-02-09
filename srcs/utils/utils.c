#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	export_traductor(t_token *token, char *envp[], t_shell *shell)
{
	t_token	*current;
	char	*processed_str;

	current = token;
	while (current)
	{
		special_cases_export_traductor(current, shell);
		if (position_dollar(current->str) != -1 && handle_exit_code(token,
				shell) == 1)
		{
			printf("current str %s\n", current->str);
			processed_str = expanded_var(current->str , envp);
			printf("processed str %s\n", processed_str);
			if (processed_str)
			{
				free(current->str);
				current->str = processed_str;
			}
		}
		current = current->next;
	}
}

void	special_cases_export_traductor(t_token *current, t_shell *shell)
{
	if (handle_exit_code(current, shell) == 0)
		current = current->next;
}

int	handle_exit_code(t_token *token, t_shell *shell)
{
	char	*exit_str;

	if (ft_strcmp("$?", token->str) == 0)
	{
		exit_str = ft_itoa(shell->exit_code);
		if (exit_str)
		{
			free(token->str);
			token->str = exit_str;
			return (0);
		}
	}
	return (1);
}
