#include "minishell.h"

void	no_pipes(t_token *token, t_shell *shell)
{
	t_token* current;

	current = token;
	while(current->type != CMD && current->type != BUILTIN)
		current = current->next;
	if (current->type == CMD)
		cmd_wo_pipes(current, shell);
	if (current->type == BUILTIN)
		builtin_wo_pipes(token, shell);
}


void	builtin_wo_pipes(t_token *token, t_shell *shell)
{
	int original_stdout;

	original_stdout = dup(STDOUT_FILENO);
	handle_file_redirection(token);
	identify_builtin(token, shell);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdout);
}

void	identify_builtin(t_token *token, t_shell *shell)
{
	t_token	*current;

	current = token;
	handle_file_redirection(current);
	if (ft_strcmp("echo", token->str) == 0)
	{
		if (current->next)
			current = current->next;
		while(current && current->type == ARG)
		{
			current->str = strip_quotes(current->str);
			current = current->next;
		}
		ft_echo(token, shell, shell->env);
	}
	if (ft_strcmp("pwd", token->str) == 0)
		ft_pwd();
	if (ft_strcmp("cd", token->str) == 0)
		cd_builtin(token, shell->env);
	if (ft_strcmp("export", token->str) == 0)
		printf("EXPORT DEEZ NUTS\n");
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
		execve(token->full_path, token->full_cmd, shell->env);
		return ;
	}
	waitpid(pid, NULL, 0);
	ft_free_array(token->full_cmd);
}