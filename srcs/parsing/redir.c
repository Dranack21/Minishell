#include "minishell.h"

void	prepare_heredoc(t_token *token)
{
	t_token *current;
	t_token *file;
	t_token *backward;

	current = token;
	while (current)
	{
		if (current->type == HERE_DOC)
		{
			if (!current->next)
				return;
			file = current->next;
			backward = current;
			while (backward && backward->type != CMD
				&& backward->type != BUILTIN && backward->type != -1)
				backward = backward->prev;
			if (backward && (backward->type == CMD || backward->type == BUILTIN 
				|| backward->type == -1))
			{
				backward->file_redir = ft_strdup(file->str);
				backward->type = HERE_DOC;
				if (process_heredoc(backward) != 0)
					printf("dedge heredoc\n");
			}
		}
		current = current->next;
	}
}
int process_heredoc(t_token *token)
{
    int fd;
    char *line;

    fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) 
        return -1;
    while (1)
    {
        line = readline("heredoc> ");
        if (line == NULL || ft_strcmp(line, token->file_redir) == 0)
        {
            free(line);
            break;
        }
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    close(fd);
    token->type = HERE_DOC;
    return 0;
}


void	prepare_redir(t_token *token)
{
	t_token	*current;
	t_token	*file;
	t_token	*backward;

	current = token;
	while (current)
	{
		if (current->type == OUPUT || current->type == APPEND_REDIR)
		{
			if (current->next)
				file = current->next;
			backward = current;
			while (backward && backward->type != CMD
				&& backward->type != BUILTIN && backward->type != -1)
				backward = backward->prev;
			if (backward && (backward->type == CMD || backward->type == BUILTIN
					|| backward->type == -1))
			{
				if (current->type == APPEND_REDIR)
				{
					backward->file_redir = ft_strdup(file->str);
					backward->int_redir = O_APPEND;
				}
				else if (current->type == OUPUT)
				{
					backward->file_redir = ft_strdup(file->str);
					backward->int_redir = O_WRONLY | O_CREAT | O_TRUNC;
				}
			}
		}
		current = current->next;
	}
}

void	prepare_redir_input(t_token *token)
{
	t_token	*current;
	t_token	*file;
	t_token	*backward;

	current = token;
	while (current)
	{
		if (current->type == INPUT)
		{
			if (current->next)
				file = current->next;
		}
		backward = current;
		while (backward && backward->type != CMD && backward->type != BUILTIN
			&& backward->type != -1)
			backward = backward->prev;
		if (backward && (backward->type == CMD || backward->type == BUILTIN
				|| backward->type == -1))
		{
			if (current->type == INPUT)
			{
				backward->file_redir = ft_strdup(file->str);
				backward->int_redir = INPUT;
			}
		}
		current = current->next;
	}
}

void	handle_file_redirection(t_token *cmd_token)
{
	int	fd;

	if (cmd_token->int_redir != 0 && cmd_token->file_redir != NULL
		&& cmd_token->int_redir != INPUT)
	{
		if (cmd_token->int_redir == O_APPEND)
			fd = open(cmd_token->file_redir, O_WRONLY | O_APPEND | O_CREAT,
					0644);
		else if (cmd_token->int_redir == 577)
		{
			fd = open(cmd_token->file_redir, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
		}
		if (fd < 0)
		{
			perror("open");
			exit(1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (cmd_token->int_redir != 0 && cmd_token->file_redir != NULL)
	{
		if (cmd_token->type == HERE_DOC)
		{
			fd = open(".heredoc", O_RDONLY);
			if (fd < 0)
			{
				perror("heredoc open");
				exit(1);
			}
			if (dup2(fd, STDIN_FILENO) < 0)
			{
				perror("dup2 heredoc");
				exit(1);
			}
			close(fd);
			unlink(".heredoc");
			return;
		}
		if (cmd_token->int_redir == INPUT)
			fd = open(cmd_token->file_redir, O_RDONLY);
		if (fd < 0)
		{
			perror("open");
			exit(1);
		}
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			perror("dup2");
			exit(1);
		}
		close(fd);
	}
}