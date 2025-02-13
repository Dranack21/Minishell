/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:04:59 by habouda           #+#    #+#             */
/*   Updated: 2025/02/13 01:00:49 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_main(t_shell *shell, t_token *token)
{
	t_token	*current;

	current = token;
	shell->pipe_count = count_pipes(token);
	if (shell->pipe_count == 0)
		no_pipes(token, shell);
	else
		create_pipes(shell, token);
	while (current)
	{
		if (current->heredoc_file)
			unlink(current->heredoc_file);
		current = current->next;
	}
	free_token_tab(token);
}

void	redirect_exe(t_shell *shell, t_token *token, t_pipe *pipe)
{
	t_token	*cmd_token;
	t_token	*temp;

	cmd_token = token;
	apply_pipe_redirection(shell, pipe);
	skip_to_good_pipe(&cmd_token, pipe);
	temp = check_pipe_line(cmd_token);
	if (temp && temp->type == ARG)
	{
		write(2, temp->str, ft_strlen(temp->str));
		if (ft_strncmp(temp->str, "/", 1) == 0)
			write(2, ": No such file or directory \n", 30);
		else
			write(2, ": command not found\n", 21);
		free_child(token, shell, pipe);
		exit(127);
	}
	temp = cmd_token;
	apply_file_redir_and_go_to_cmd_token(&cmd_token);
	if (cmd_token && cmd_token->type == CMD)
		execute_cmd(cmd_token, shell);
	else if (cmd_token && cmd_token->type == BUILTIN)
		builtin_with_pipes(cmd_token, shell, pipe);
	else if (is_redir(cmd_token) == EXIT_FAILURE)
		mini_x(token, shell, pipe, temp);
}

void	apply_pipe_redirection(t_shell *shell, t_pipe *pipe)
{
	if (pipe->id == 0)
		dup2(pipe->fd[1], STDOUT_FILENO);
	else if (pipe->id == shell->pipe_count)
		dup2(pipe->prev->fd[0], STDIN_FILENO);
	else
	{
		dup2(pipe->prev->fd[0], STDIN_FILENO);
		dup2(pipe->fd[1], STDOUT_FILENO);
	}
}

void	apply_file_redir_and_go_to_cmd_token(t_token **cmd_token)
{
	while (*cmd_token && (*cmd_token)->type != CMD
		&& (*cmd_token)->type != BUILTIN)
	{
		*cmd_token = (*cmd_token)->next;
	}
	if (!(*cmd_token))
		return ;
	if ((*cmd_token)->int_redir_out != 0
		&& (*cmd_token)->file_redir_out != NULL)
	{
		handle_file_redirection(*cmd_token);
	}
	if ((*cmd_token)->int_redir != 0 && (*cmd_token)->file_redir != NULL
		&& (*cmd_token)->heredoc_file != NULL)
	{
		handle_file_redirection(*cmd_token);
	}
	if ((*cmd_token)->int_redir != 0 && (*cmd_token)->file_redir != NULL
		&& (*cmd_token)->heredoc_file == NULL)
	{
		handle_file_redirection(*cmd_token);
	}
}

void	execute_cmd(t_token *token, t_shell *shell)
{
	if (token->is_valid == IS_NOT_VALID)
	{
		write(STDERR_FILENO, token->str, ft_strlen(token->str));
		write(STDERR_FILENO, " : command not found", 21);
		exit(127);
	}
	token->full_cmd = create_cmd_tab(token);
	if (token->full_cmd && token->full_path)
	{
		if (ft_strncmp(token->str, "/", 1) == 0)
			handle_err_execve(token);
		else if (execve(token->full_path, token->full_cmd, shell->env) == -1)
			handle_err_execve(token);
		else
			shell->exit_code = 0;
		ft_free_array(token->full_cmd);
	}
}
