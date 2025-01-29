#include "minishell.h"

//// FREE DU TABLEAU DE TOKEN LORS DE SA CREATION ET ASSIGNATION DE CHAQUE STR
///////

void	free_token_tab(t_token *head)
{
	t_token	*temp;

	while (head != NULL)
	{
		temp = head->next;
		free(head->str);
		if (head->full_path != NULL)
			free(head->full_path);
		if (head->file_redir != NULL)
			free(head->file_redir);
		if (head->heredoc_file != NULL)
			free(head->heredoc_file);
		free(head);
		head = temp;
	}
}

void	free_pipes(t_pipe *pipe)
{
	t_pipe	*temp;

	while (pipe)
	{
		temp = pipe->next;
		free(pipe);
		pipe = temp;
	}
}
