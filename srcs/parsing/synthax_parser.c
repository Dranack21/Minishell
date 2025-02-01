#include "minishell.h"

int	synthax_parser(t_token *token)
{
	if (check_pipes_parser(token) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_for_redirs_parser(token) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_for_redirs_parser(t_token *token)
{
	t_token	*current;

	current = token;
	while(current)
	{
		if (is_redir(current) == EXIT_SUCCESS && current->next)
		{
			if (is_redir(current->next) == EXIT_SUCCESS)
				return (EXIT_FAILURE);
		}
		current = current->next;
	}
	current = token;
	while (current->next)
		current = current->next;
	if (current && is_redir(current) == EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int is_redir(t_token *current)
{
    if (current && 
        (current->type == HERE_DOC || 
         current->type == OUPUT || 
         current->type == INPUT || 
         current->type == APPEND_REDIR))
        return (EXIT_SUCCESS);
    return (EXIT_FAILURE);
}

int	check_pipes_parser(t_token *token)
{
	t_token	*current;

	current = token;
	if (current && current->type == PIPE)
		return (EXIT_FAILURE);
	while (current)
	{
		if (current->type == PIPE && current->next)
		{
			if (current->next && current->next->type == PIPE)
				return (EXIT_FAILURE);
		}
		if (is_redir(current) == EXIT_SUCCESS)
		{
			if (!current->next || (current->next && current->next->type == PIPE))
				return (EXIT_FAILURE);
		}
		current = current->next;
	}
	current = token;
	while (current->next)
		current = current->next;
	if (current && current->type == PIPE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
