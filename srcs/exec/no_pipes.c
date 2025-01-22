#include "minishell.h"

void	no_pipes(t_token *token, t_shell *shell)
{
	t_token* current;

	current = token;
	while(current->type != CMD && current->type != BUILTIN)
		current = current->next;
	if (current->type == CMD || current->type == BUILTIN)
		cmd_wo_pipes(current, shell);
}

void	cmd_wo_pipes(t_token *token, t_shell *shell)
{
	pid_t	pid;

	printf("aaa\n");
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

// void	builtin_wo_pipes(t_token *token)
// {
// }
