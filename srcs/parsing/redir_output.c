#include "minishell.h"

void	prepare_redir_output(t_token *token)
{
	t_token	*current;
	t_token	*file;
	t_token	*back;

	current = token;
	while (current)
	{
		if (current->type == OUPUT || current->type == APPEND_REDIR)
		{
			if (current->next)
				file = current->next;
			back = find_cmd_token_redir(current, -1);
			if (!back)
				back = find_cmd_token_redir(current, 1);
			if (back && (back->type == CMD || back->type == BUILTIN))
				apply_output_redirection(back, file, current);
		}
		current = current->next;
	}
}

t_token	*find_cmd_token_redir(t_token *current, int direction)
{
	t_token	*back;

	back = current;
	while (back && back->type != CMD && back->type != BUILTIN)
	{
		if (direction == 1)
			back = back->next;
		else
			back = back->prev;
	}
	return (back);
}

void	apply_output_redirection(t_token *back, t_token *file, t_token *current)
{
	int	fd;

	if (current->type == APPEND_REDIR)
	{
		back->file_redir = ft_strdup(file->str);
		back->int_redir = O_APPEND;
		fd = open(back->file_redir, O_CREAT, 0644);
		if (fd < 0)
			perror(back->file_redir);
		else
			close(fd);
	}
	else if (current->type == OUPUT)
	{
		back->file_redir = ft_strdup(file->str);
		back->int_redir = O_WRONLY | O_CREAT | O_TRUNC;
		fd = open(back->file_redir, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			perror(back->file_redir);
		else
			close(fd);
	}
}
