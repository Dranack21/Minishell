#include "minishell.h"

void	handle_file_redirection(t_token *cmd_token)
{
	int	fd;
	fd = 0;

	if (cmd_token->int_redir_out != 0 && cmd_token->file_redir_out != NULL)
	{
		handle_ouput_redirection(cmd_token, fd);
	}
	if (cmd_token->int_redir != 0 && cmd_token->file_redir != NULL
		&& cmd_token->heredoc_file != NULL)
	{
		handle_heredoc_redirection(cmd_token, fd);
	}
	if (cmd_token->int_redir != 0 && cmd_token->file_redir != NULL && cmd_token->heredoc_file == NULL)
		handle_input_redirection(cmd_token, fd);
}

void	handle_ouput_redirection(t_token *cmd_token, int fd)
{
	if (cmd_token->int_redir_out == O_APPEND)
	{
		fd = open(cmd_token->file_redir_out, O_WRONLY | O_APPEND | O_CREAT, 0644);
		fprintf(stderr, "messire suis-je rentrer ici\n");
	}
	else if (cmd_token->int_redir_out == 577)
	{
		fd = open(cmd_token->file_redir_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_input_redirection(t_token *cmd_token, int fd)
{
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

void	handle_heredoc_redirection(t_token *cmd_token, int fd)
{
	if (cmd_token->int_redir == HERE_DOC)
	{
		fprintf(stderr ,"heredoc file name %s\n",cmd_token->heredoc_file);
		fd = open(cmd_token->heredoc_file, O_RDONLY);
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
	}
}

t_token	*find_cmd_token_redir(t_token *current, int direction)
{
	t_token	*back;

	back = current;
	while (back && back->type != CMD && back->type != BUILTIN && back->type != PIPE)
	{
		if (direction == 1)
			back = back->next;
		else
			back = back->prev;
	}
	if (back && back->type == PIPE)
	{
		while (back)
			back = back->next;
	}
	return (back);
}