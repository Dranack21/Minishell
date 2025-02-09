#include "minishell.h"

void	verify_all(t_shell *shell, t_token *token)
{
	shell->pipe_count = count_pipes(token);
	if (shell->pipe_count == 0)
	{
		verify_for_no_pipes(token);
		verify_for_args(token);
	}
	else if (shell->pipe_count > 0)
	{
		verify_for_pipes(token);
	}
}

void	verify_for_no_pipes(t_token *token)
{
	t_token	*current;

	current = token;
	if (pipeline_destroyer(current) == EXIT_FAILURE)
		current->is_valid = IS_NOT_VALID;
}

void	verify_for_pipes(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (pipeline_destroyer(current) == EXIT_FAILURE)
		{
			while (current && current->type != PIPE)
			{
				current->is_valid = IS_NOT_VALID;
				if (current->next)
					current = current->next;
				else
					break ;
			}
		}
		while (current && current->type != PIPE)
		{
			current = current->next;
		}
		if (current && current->type == PIPE)
			current = current->next;
	}
}

int	pipeline_destroyer(t_token *token)
{
	if (token->type == CMD)
		return (EXIT_SUCCESS);
	if (token->type == BUILTIN)
		return (EXIT_SUCCESS);
	if (token->type == HERE_DOC)
		return (EXIT_SUCCESS);
	if (token->type == OUPUT)
		return (EXIT_SUCCESS);
	if (token->type == APPEND_REDIR)
		return (EXIT_SUCCESS);
	if (token->type == INPUT)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

void	verify_for_args(t_token *token)
{
	t_token	*current;
	int		cmd;

	cmd = 0;
	current = token;
	while (current && current->type != PIPE)
	{
		if (current->type == CMD || current->type == BUILTIN)
			cmd = 1;
		if (current->type == ARG)
		{
			if (cmd == 0)
				current->is_valid = IS_NOT_VALID;
		}
		current = current->next;
	}
	return ;
}
