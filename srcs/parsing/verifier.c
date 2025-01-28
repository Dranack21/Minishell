#include "minishell.h"


void	verify_all(t_shell *shell, t_token *token)
{
	t_token	*current;

	current = token;
	shell->pipe_count = count_pipes(token);
	if (shell->pipe_count == 0)
		return ;
	else if (shell->pipe_count > 0)	
		verify_for_pipes(token);
}

void verify_for_pipes(t_token *token)
{
    t_token *current;
    int     i;

    i = 0;
    current = token;
    while (current)
    {
        if (pipeline_destroyer(current) == EXIT_FAILURE)
            current->is_valid = IS_NOT_VALID;
        while (current && current->type != PIPE)
            current = current->next;
        if (current && current->type == PIPE)
            current = current->next;
    }
}

int	pipeline_destroyer(t_token	*token)
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
