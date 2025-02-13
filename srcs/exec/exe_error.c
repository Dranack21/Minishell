/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:04:57 by habouda           #+#    #+#             */
/*   Updated: 2025/02/13 00:48:27 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_execve_error(char *str, t_token *token, struct stat *stats)
{
	if (errno == ENOENT && !strchr(token->str, '/'))
		printf("%s: %s: command not found\n", str, token->str);
	else if (errno == ENOENT)
		printf("%s: %s: No such file or directory\n", str, token->str);
	else if (stat(token->str, stats) != -1)
	{
		if (S_ISDIR(stats->st_mode) == 1)
			printf("%s: %s: Is a directory\n", str, token->str);
		else if (errno == EACCES)
			printf("%s: %s: Permission denied\n", str, token->str);
		else
			printf("%s: %s\n", token->str, strerror(errno));
	}
	else
		printf("%s: %s: No such file or directory\n", str, token->str);
}

void	handle_err_execve(t_token *token)
{
	int			tmp_fd;
	char		*str;
	struct stat	stats;

	tmp_fd = dup(STDOUT_FILENO);
	if (tmp_fd == -1)
		return (perror("dup failed"));
	str = get_prompt_name(token);
	if (str == NULL)
		str = ft_strdup("Minishell");
	if (dup2(STDERR_FILENO, STDOUT_FILENO) == -1)
	{
		perror("dup2 failed");
		free(str);
		return ;
	}
	print_execve_error(str, token, &stats);
	free(str);
	if (dup2(tmp_fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 failed");
		return ;
	}
	close(tmp_fd);
}

char	*get_prompt_name(t_token *token)
{
	t_token		*current;
	struct stat	st;

	current = token;
	while (current && current->type != PIPE)
	{
		if (current->type == CMD && access(token->full_path, X_OK) == 0
			&& stat(token->full_path, &st) == 0 && S_ISREG(st.st_mode))
			break ;
		if (current->prev)
			current = current->prev;
		else
			break ;
	}
	if (!current->prev)
		return (NULL);
	return (ft_strdup(current->str));
}

void	mini_x(t_token *token, t_shell *shell, t_pipe *pipe, t_token *temp)
{
	write(STDERR_FILENO, temp->str, ft_strlen(temp->str));
	write(STDERR_FILENO, " : command not found\n", 22);
	free_child(token, shell, pipe);
	exit(127);
}
