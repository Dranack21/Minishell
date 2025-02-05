#include "minishell.h"

void	handle_file_redirection(t_token *cmd_token)
{
	int	fd;

	fd = 0;
	if (cmd_token->int_redir != 0 && cmd_token->file_redir != NULL
		&& cmd_token->int_redir != INPUT && cmd_token->int_redir != HERE_DOC)
	{
		handle_ouput_redirection(cmd_token, fd);
	}
	else if (cmd_token->int_redir != 0 && cmd_token->file_redir != NULL
		&& cmd_token->heredoc_file != NULL)
	{
		handle_heredoc_redirection(cmd_token, fd);
	}
	else if (cmd_token->int_redir != 0 && cmd_token->file_redir != NULL)
		handle_input_redirection(cmd_token, fd);
}

void	handle_ouput_redirection(t_token *cmd_token, int fd)
{
	if (cmd_token->int_redir == O_APPEND)
		fd = open(cmd_token->file_redir, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (cmd_token->int_redir == 577)
	{
		fd = open(cmd_token->file_redir, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
	{
		if (cmd_token->int_redir == HERE_DOC)
		{
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
			unlink(cmd_token->heredoc_file);
			return ;
		}
	}
}
