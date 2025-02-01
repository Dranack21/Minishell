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
	int		i;

	i = 0;
	cmd_token = token;
	if (pipe->id == 0)
		dup2(pipe->fd[1], STDOUT_FILENO);
	else if (pipe->id == shell->pipe_count)
		dup2(pipe->prev->fd[0], STDIN_FILENO);
	else
	{
		dup2(pipe->prev->fd[0], STDIN_FILENO);
		dup2(pipe->fd[1], STDOUT_FILENO);
	}
	while (i != pipe->id)
	{
		if (cmd_token->type == PIPE)
			i++;
		cmd_token = cmd_token->next;
	}
	temp = cmd_token;
	while (temp && temp->type != PIPE)
	{
		if (temp->int_redir != 0 && cmd_token->file_redir != NULL)
			handle_file_redirection(temp);
		temp = temp->next;
	}
	temp = cmd_token;
	while (cmd_token && cmd_token->type != CMD && cmd_token->type != BUILTIN)
	{
		if (cmd_token->next)
			cmd_token = cmd_token->next;
		else
			break;
	}
	close_unused_pipes(pipe);
	if (cmd_token->type == CMD)
		execute_cmd(token, shell, pipe);
	else if (cmd_token->type == BUILTIN)
		builtin_wo_pipes(token, shell);
	else
		fprintf(stderr, "%s : command not found gros bouffon\n", temp->str);
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
		fprintf(stderr, "%s : command not found gros bouffon", token->str);
		return ;
	}
	token->full_cmd = create_cmd_tab(token);
	if (token->full_cmd && token->full_path)
	{
		// Print to stderr before execve
		for (int j = 0; token->full_cmd[j]; j++)
			fprintf(stderr, "arg[%d]: '%s'\n", j, token->full_cmd[j]);
		if (execve(token->full_path, token->full_cmd, shell->env) == -1)
			handle_err_execve(token);
		ft_free_array(token->full_cmd);
	}
}
