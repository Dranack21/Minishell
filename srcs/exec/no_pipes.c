#include "minishell.h"

void	no_pipes(t_token *token, t_shell *shell)
{
	t_token	*current;

	current = token;
	if (current->is_valid == IS_NOT_VALID)
	{
		printf("%s : command not found\n", token->str);
		while(current)
		{
			current->is_valid = IS_NOT_VALID;
			current = current->next;
		}
	}
	current = token;
	while (current->type != CMD && current->type != BUILTIN && current->next)
		current = current->next;
	if (current->type == CMD && current)
		cmd_wo_pipes(current, shell);
	if (current->type == BUILTIN && current)
		builtin_wo_pipes(token, shell);
}

void	builtin_wo_pipes(t_token *token, t_shell *shell)
{
	int	original_stdout;

	original_stdout = dup(STDOUT_FILENO);
	handle_file_redirection(token);
	if (token->is_valid == IS_VALID)
	{
		identify_builtin(token, shell);
		dup2(original_stdout, STDOUT_FILENO);
		close(original_stdout);
	}
}

void	identify_builtin(t_token *token, t_shell *shell)
{
	if (ft_strcmp("echo", token->str) == 0)
		ft_echo(token, shell, shell->env);
	if (ft_strcmp("pwd", token->str) == 0)
		ft_pwd();
	if (ft_strcmp("cd", token->str) == 0)
		cd_builtin(token, shell->env);
	if (ft_strcmp("export", token->str) == 0)
		ft_export(token, &shell->env, shell);
	if (ft_strcmp("unset", token->str) == 0)
		ft_unset(token, shell->env);
	if (ft_strcmp("env", token->str) == 0)
		ft_envp(shell->env);
	if (ft_strcmp("exit", token->str) == 0)
		ft_exit(token);
}

void	cmd_wo_pipes(t_token *token, t_shell *shell)
{
	pid_t	pid;

	token->full_cmd = create_cmd_tab(token);
	if (!token->full_cmd && !token->full_path)
		return ;
	pid = fork();
	if (pid == 0)
	{
		for (int j = 0; token->full_cmd[j]; j++)
			fprintf(stderr, "arg[%d]: '%s'\n", j, token->full_cmd[j]);
		handle_file_redirection(token);
		if (token->is_valid == IS_VALID)
			if (execve(token->full_path, token->full_cmd, shell->env) == -1)
				handle_err_execve(token);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	ft_free_array(token->full_cmd);
}
