#include "minishell.h"

void	builtin_with_pipes(t_token *token, t_shell *shell, t_pipe *pipe)
{
	int	original_stdout;
	int	i;

	i = -1;
	original_stdout = dup(STDOUT_FILENO);
	handle_file_redirection(token);
	if (token->is_valid == IS_VALID)
	{
		i = identify_builtin_pipes(token, shell);
		dup2(original_stdout, STDOUT_FILENO);
		close(original_stdout);
	}
	if (i != -1)
	{
		free_child(token, shell, pipe);
		exit(i);
	}
}

int	identify_builtin_pipes(t_token *token, t_shell *shell)
{
	int i;

	i = -1;
	if (ft_strcmp("echo", token->str) == 0)
	{
		ft_echo(token, shell->env);
		shell->exit_code = 0;
	}
	if (ft_strcmp("pwd", token->str) == 0)
	{
		ft_pwd(shell);
	}
	if (ft_strcmp("cd", token->str) == 0)
		cd_builtin(shell, token, shell->env);
	if (ft_strcmp("export", token->str) == 0)
		ft_export(token, &shell->env, shell);
	if (ft_strcmp("unset", token->str) == 0)
	{
		ft_unset(token, shell->env);
		shell->exit_code = 0;
	}
	if (ft_strcmp("env", token->str) == 0)
		ft_envp(shell->env, shell);
	if (ft_strcmp("exit", token->str) == 0)
	{
		i = ft_exit(shell, token);
	}
	return (i);
}
