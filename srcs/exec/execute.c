#include "minishell.h"

void	execute(t_shell *shell, t_token *token, char *envp[])
{
	int	pipe_count;

	pipe_count = count_pipes(token);
	if (pipe_count == 0)
		return ;
	else
		create_pipes(shell, token, envp);

}

void	create_pipes(t_shell *shell, t_token *token, char env)
{
	t_pipe		*head;
	t_pipe		*current;
	int			i;
	int			temp;

	i = 0;
	temp = shell->pipe_count;
	head = NULL;
	while (temp >= 0)
	{
		ft_add_in_list_pipes(&head);
		temp--;
	}
	while (current != NULL)
	{
		current->id = i;
		i++;
	}
	current = head;
	while(current !=NULL)
	{
		current->pid = fork();
		if (current->pid == 0)
		{
			redirect_exe(shell, token, current);
			exit(0);
		}
		current = current->next;
	}
}


void	redirect_exe(t_shell *shell, t_token *token, t_pipe *pipe)
{ 
	if (pipe->id == 0)
		first_cmd();
	if (pipe->id == shell->pipe_count - 1)
		last_cmd();
	else
		execute_cmd(shell, token, pipe);
}

void	execute_cmd(t_shell *shell, t_token *token, t_pipe *pipe)
{
	
}
