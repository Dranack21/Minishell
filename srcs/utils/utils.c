#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	skip_string_in_quotes(char *rl, int i)
{
	i++;
	while (rl[i] && rl[i] != '"')
		i++;
	if (rl[i] == '"')
		i++;
	return (i);
}

int	skip_string_in_single_quotes(char *rl, int i)
{
	i++;
	while (rl[i] && rl[i] != '\'')
		i++;
	if (rl[i] == '\'')
		i++;
	return (i);
}

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
			processed_str = process_dollar_string(current->str, envp,
					current->quote_type);
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
	if (current->prev && !ft_strcmp("unset", current->prev->str))
	{
		current = current->next;
	}
	if (handle_exit_code(current, shell) == 0)
	{
		current = current->next;
	}
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
