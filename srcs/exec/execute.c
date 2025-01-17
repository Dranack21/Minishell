#include "minishell.h"

void	execute_main(t_shell *shell, t_token *token)
{
	shell->pipe_count = count_pipes(token);
	if (shell->pipe_count == 0)
		return ;
	else
		create_pipes(shell, token);

}

void	create_pipes(t_shell *shell, t_token *token)
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
	current = head;
	while (current != NULL)
	{
		current->id = i;
		printf("Pipe créé : ID = %d\n", current->id);
		current = current->next;
		i++;
	}
	current = head;
	while(current != NULL)
	{
		current->pid = fork();
		if (current->pid == 0)
		{
			printf("Process %d: forked with PID %d\n", current->id, current->pid);
			redirect_exe(shell, token, current);
			exit(0);
		}
		current = current->next;
	}
	current = head;
	while (current != NULL)
	{
    	waitpid(current->pid, NULL, 0);
    	current = current->next;
	}
}

void	redirect_exe(t_shell *shell, t_token *token, t_pipe *pipe)
{ 
	if (pipe->id == 0)
		dup2(pipe->fd[1],STDOUT_FILENO);
	if (pipe->id == shell->pipe_count)
	{
		dup2(pipe->fd[0],STDIN_FILENO);
	}
	else
	{
		printf("pipe id test %d\n", pipe->id);
		dup2(pipe->fd[1], STDOUT_FILENO);
		dup2(pipe->prev->fd[0], STDIN_FILENO);
		execute_cmd(token, shell, pipe);
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
	while(token->type != CMD)
		token = token->next;
	token->full_cmd =create_cmd_tab(token);
	printf("a?\n");
	execve(token->full_path, token->full_cmd, shell->env);
	ft_print_array(token->full_cmd);
	ft_free_array(token->full_cmd);
}

char	**create_cmd_tab(t_token *token)
{
	int		i;
	int		count;
	char	**cmd;

	count = count_for_cmd_tab(token);
	i = 0;
	cmd = malloc(sizeof(char*) * count + 1);
	while (token)
    {
        if (token->type == CMD || token->type == BUILTIN)
        {
            cmd[i++] = ft_strdup(token->str);
            token = token->next;
            while (token && token->type == ARG)
            {
                cmd[i++] = ft_strdup(token->str);
                token = token->next;
            }
            break;
        }
        token = token->next;
    }
    cmd[i] = NULL;
    return (cmd);
}

int	count_for_cmd_tab(t_token *token)
{
	int		count;
	t_token	*current;

	current = token;
	count = 0;
	while(current)
	{
		if (current->type == CMD || current->type == BUILTIN)
		{
			count++;
			current = current->next;
			while (current && current->type == ARG)
			{
				count++;
				current = current->next;
			}
			break;
		}
		current = current->next;
	}
	return(count);
}

