#include "minishell.h"

int	apply_heredoc_redir(t_token *backward, t_token *file, t_shell *shell,
		t_token *current)
{
	if (current->type == HERE_DOC)
	{
		if (process_heredoc(backward, shell, file) != 0)
			return (EXIT_FAILURE);
		if (!backward)
		{
			fprintf(stderr, "JE SUIS LA\n");
			return (EXIT_FAILURE);
		}
		if (backward->file_redir)
			free(backward->file_redir);
		backward->file_redir = ft_strdup(file->str);
		backward->int_redir = HERE_DOC;
	}
	return (EXIT_SUCCESS);
}

int	apply_file_redir(t_token *backward, t_token *file, t_token *current)
{
	int	fd;

	fd = 0;
	if (current->type == INPUT)
	{
		fd = open(file->str, O_RDONLY);
		if (fd < 0)
			return (perror("open"), EXIT_FAILURE);
		close(fd);
		if (!backward)
			return (EXIT_FAILURE);
		if (backward->file_redir)
			free(backward->file_redir);
		backward->file_redir = ft_strdup(file->str);
		backward->int_redir = INPUT;
		backward->heredoc_file = NULL;
	}
	return (EXIT_SUCCESS);
}
