/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:05:29 by habouda           #+#    #+#             */
/*   Updated: 2025/02/09 23:05:57 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_heredoc_child(int fd, t_token *token, t_shell *shell,
		t_token *file)
{
	char	*line;
	char	*expanded_line;

	ft_setup_heredoc_signals();
	while (1)
	{
		line = readline("heredoc> ");
		if (line == NULL || ft_strcmp(line, file->str) == 0)
		{
			free(line);
			break ;
		}
		expanded_line = search_if_env(line, shell->env);
		write(fd, expanded_line, ft_strlen(expanded_line));
		write(fd, "\n", 1);
		free(expanded_line);
	}
	free(token->heredoc_file);
	free_inside_heredoc(token, shell);
	close(fd);
	exit(0);
}

static void	handle_heredoc_parent(pid_t pid1, t_shell *shell,
		char *heredoc_file, int status)
{
	waitpid(pid1, &status, 0);
	if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		shell->exit_code = status;
	}
	if (status == 130)
		open(heredoc_file, O_TRUNC);
}

int	prepare_redir_input(t_token *token, t_shell *shell)
{
	t_token	*current;
	t_token	*file;
	t_token	*back;
	int		i;

	i = 0;
	current = token;
	while (current)
	{
		if (current->type == HERE_DOC || current->type == INPUT)
		{
			file = current->next;
			back = find_cmd_token_redir(current, -1);
			if (!back)
				back = find_cmd_token_redir(current, 1);
			i = process_backward_heredoc(back, file, shell, current);
		}
		current = current->next;
	}
	return (i);
}

int	process_backward_heredoc(t_token *backward, t_token *file, t_shell *shell,
		t_token *current)
{
	int	fd;

	if (current->type == HERE_DOC)
	{
		if (process_heredoc(backward, shell, file) != 0)
			return (EXIT_FAILURE);
		if (!backward)
			return (EXIT_FAILURE);
		backward->file_redir = ft_strdup(file->str);
		backward->int_redir = HERE_DOC;
	}
	if (current->type == INPUT)
	{
		fd = open(file->str, O_RDONLY);
		if (fd < 0)
			return (perror("open"), EXIT_FAILURE);
		close(fd);
		if (!backward)
			return (EXIT_FAILURE);
		backward->file_redir = ft_strdup(file->str);
		backward->int_redir = INPUT;
		backward->heredoc_file = NULL;
	}
	return (EXIT_SUCCESS);
}

int	process_heredoc(t_token *token, t_shell *shell, t_token *file)
{
	int		fd;
	char	*heredoc_file;
	int		status;
	pid_t	pid1;

	status = 0;
	if (init_heredoc(&heredoc_file, &fd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	pid1 = fork();
	if (pid1 == 0)
		handle_heredoc_child(fd, token, shell, file);
	else
		handle_heredoc_parent(pid1, shell, heredoc_file, status);
	if (token)
		token->heredoc_file = heredoc_file;
	return (close(fd), ft_restore_signals(), 0);
}
