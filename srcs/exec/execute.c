#include "minishell.h"

void    execute_main(t_shell *shell, t_token *token)
{
    shell->pipe_count = count_pipes(token);
    if (shell->pipe_count == 0)
        return ;
    else
        create_pipes(shell, token);

}

void create_pipes(t_shell *shell, t_token *token)
{
    t_pipe *head;
    t_pipe *current;
    int i;
    int temp;

    i = 0;
    temp = shell->pipe_count;
    printf("pipe count %d\n", temp);
    head = NULL;
    //// CREATE LIST ////
    while (temp >= 0)
    {
        ft_add_in_list_pipes(&head);
        temp--;
    }
    current = head;
    //// CREATE PIPE////
    while (current->next != NULL)
    {
        if (pipe(current->fd) == -1)
        {
            perror("pipe");
            exit(1);
        }
        current = current->next;
    }
    current = head;
    while (current != NULL)
    {
        current->id = i++;
		printf("created pipe ID : %d\n", current->id);
        current = current->next;
    }
    //// FORK ////
    current = head;
    while(current != NULL)
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
    current = head;
    while (current->next != NULL)
    {
        close(current->fd[0]);
        close(current->fd[1]);
        current = current->next;
    }
    current = head;
    //// wait for childs ////
    while (current != NULL)
    {
        waitpid(current->pid, NULL, 0);
        current = current->next;
    }
    free_pipes(head);
}

void redirect_exe(t_shell *shell, t_token *token, t_pipe *pipe)
{
    if (pipe->id == 0) 
	{
        dup2(pipe->fd[1], STDOUT_FILENO);
    } 
    else if (pipe->id == shell->pipe_count) 
	{
        dup2(pipe->prev->fd[0], STDIN_FILENO);
    } 
    else 
	{
        dup2(pipe->prev->fd[0], STDIN_FILENO);
        dup2(pipe->fd[1], STDOUT_FILENO);
    }
    close_unused_pipes(pipe);
    execute_cmd(token, shell, pipe);
}

void    execute_cmd(t_token *token, t_shell *shell, t_pipe *pipe)
{
    int    i;

    i = 0;
    while (i != pipe->id)
    {
        if (token->type == PIPE)
            i++;
        token = token->next;
    }
    while(token->type != CMD)
        token = token->next;
    token->full_cmd = create_cmd_tab(token);
    if (token->full_cmd && token->full_path)
    {
        execve(token->full_path, token->full_cmd, shell->env);
        ft_print_array(token->full_cmd);
        ft_free_array(token->full_cmd);
    }
}
