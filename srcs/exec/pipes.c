#include "minishell.h"

void	create_pipes(t_shell *shell, t_token *token)
{
	t_pipe	*head;
	t_pipe	*current;
	int		temp;

	temp = shell->pipe_count;
	printf("pipe count %d\n", temp);
	head = NULL;
	setup_pipes(&head, temp);
	current = head;
	while (current != NULL)
	{
		current->pid = fork();
		if (current->pid == -1)
		{
			perror("fork");
			exit(1);
		}
		if (current->pid == 0)
		{
			redirect_exe(shell, token, current);
			exit(0);
		}
		current = current->next;
	}
	close_fds_and_wait_for_childs(shell, head);
	free_pipes(head);
}

void	setup_pipes(t_pipe **head, int temp)
{
	t_pipe	*current;
	int		i;

	i = 0;
	while (temp >= 0)
	{
		ft_add_in_list_pipes(head);
		temp--;
	}
	current = *head;
	while (current->next != NULL)
	{
		if (pipe(current->fd) == -1)
		{
			perror("pipe");
			exit(1);
		}
		current = current->next;
	}
	current = *head;
	while (current != NULL)
	{
		current->id = i++;
		printf("created pipe ID : %d\n", current->id);
		current = current->next;
	}
}

void	close_fds_and_wait_for_childs(t_shell *shell, t_pipe *head)
{
	t_pipe	*current;
	int		status;
	current = head;
	while (current->next != NULL)
	{
		close(current->fd[0]);
		close(current->fd[1]);
		current = current->next;
	}
	current = head;
	while (current != NULL)
	{
    waitpid(current->pid, &status, 0);
    if (WIFEXITED(status))
        shell->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
        shell->exit_code = 128 + WTERMSIG(status);
    else
    	shell->exit_code = status;
    current = current->next;
	}
}
