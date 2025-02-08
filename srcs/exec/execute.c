#include "minishell.h"

void	execute_main(t_shell *shell, t_token *token)
{
	shell->pipe_count = count_pipes(token);
	if (shell->pipe_count == 0)
		no_pipes(token, shell);
	else
		create_pipes(shell, token);
}

void	redirect_exe(t_shell *shell, t_token *token, t_pipe *pipe)
{
	t_token	*cmd_token;
	t_token	*temp;

	cmd_token = token;
	apply_pipe_redirection(shell, pipe);
	skip_to_good_pipe(cmd_token, pipe);
	temp = cmd_token;
	apply_file_redir_and_go_to_cmd_token(cmd_token, temp);
	close_unused_pipes(pipe);
	if (cmd_token->type == CMD)
		execute_cmd(token, shell, pipe);
	else if (cmd_token->type == BUILTIN)
		builtin_wo_pipes(token, shell);
	else if (is_redir(cmd_token) == EXIT_FAILURE)
	{
		fprintf(stderr, "%s : command not found gros bouffon\n", temp->str);
		exit(127);
	}
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

void	apply_file_redir_and_go_to_cmd_token(t_token *cmd_token, t_token *temp)
{
	while (temp && temp->type != PIPE)
	{
		if (temp->int_redir_out != 0 && cmd_token->file_redir_out != NULL)
			handle_file_redirection(temp);
		if (temp->int_redir != 0 && temp->file_redir != NULL
			&& temp->heredoc_file != NULL)
		{
			handle_file_redirection(temp);
		}
		if (cmd_token->int_redir != 0 && cmd_token->file_redir != NULL
			&& cmd_token->heredoc_file == NULL)
		{
			handle_file_redirection(temp);
		}
		temp = temp->next;
	}
	while (cmd_token && cmd_token->type != CMD && cmd_token->type != BUILTIN)
	{
		if (cmd_token->next)
			cmd_token = cmd_token->next;
		else
			break ;
	}
}

void	execute_cmd(t_token *token, t_shell *shell, t_pipe *pipe)
{
	int	i;

	i = 0;
	while (i != pipe->id)
	{
		if (token->type == PIPE)
			i++;
		token = token->next;
	}
	if (token->is_valid == IS_NOT_VALID)
	{
		fprintf(stderr, "%s : command not found", token->str);
		exit(127);
	}
	token->full_cmd = create_cmd_tab(token);
	if (token->full_cmd && token->full_path)
	{
		for (int j = 0; token->full_cmd[j]; j++)
			fprintf(stderr, "arg[%d]: '%s'\n", j, token->full_cmd[j]);
		if (execve(token->full_path, token->full_cmd, shell->env) == -1)
			handle_err_execve(token);
		else
			shell->exit_code = 0;
		ft_free_array(token->full_cmd);
	}
}
