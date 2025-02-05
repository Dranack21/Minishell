#include "minishell.h"

void	prepare_redir_input(t_token *token)
{
	t_token	*current;
	t_token	*file;
	t_token	*back;

	current = token;
	while (current)
	{
		if (current->type == INPUT)
		{
			if (current->next)
				file = current->next;
			back = find_cmd_token_redir(current, -1);
			if (!back)
				back = find_cmd_token_redir(current, 1);
			if (back && (back->type == CMD || back->type == BUILTIN))
				apply_input_redirection(back, file);
		}
		current = current->next;
	}
}

void	apply_input_redirection(t_token *back, t_token *file)
{
	back->file_redir = ft_strdup(file->str);
	back->int_redir = INPUT;
}
