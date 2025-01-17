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
    head = NULL;
    while (temp >= 0)
    {
        ft_add_in_list_pipes(&head);
        temp--;
    }
    current = head;
    while (current != NULL)
    {
        if (pipe(current->fd) == -1)
        {
            perror("pipe");
            exit(1);
        }
        current->id = i++;
		printf("created pipe ID : %d\n", current->id);
        current = current->next;
    }
    current = head;
    while(current->next != NULL)
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
    while (current != NULL)
    {
        close(current->fd[0]);
        close(current->fd[1]);
        current = current->next;
    }
    current = head;
    while (current != NULL)
    {
        waitpid(current->pid, NULL, 0);
        current = current->next;
    }
}

void redirect_exe(t_shell *shell, t_token *token, t_pipe *pipe)
{
    // Ensure pipes are properly closed for this specific process
    if (pipe->id == 0) 
	{
        close(pipe->fd[0]);  // Close read end (not used by the first command)
        dup2(pipe->fd[1], STDOUT_FILENO); // Redirect the write end to stdout
    } 
    else if (pipe->id == shell->pipe_count) 
	{
        dup2(pipe->prev->fd[0], STDIN_FILENO); // Redirect the previous pipe's read end to stdin
    } 
    else 
	{
        close(pipe->fd[0]);    // Close the read end of this pipe
        close(pipe->prev->fd[1]); // Close the write end of the previous pipe
        dup2(pipe->prev->fd[0], STDIN_FILENO); // Redirect input from previous pipe
        dup2(pipe->fd[1], STDOUT_FILENO); // Redirect output to current pipe
    }

    // Close all unused pipe file descriptors (this will clean up)
    close_unused_pipes(pipe);

    // Now attempt to execute the command, exit if failed
    execute_cmd(token, shell, pipe);
}

void close_unused_pipes(t_pipe *pipe)
{
    t_pipe *current = pipe;
    
    // Close unused file descriptors (pipes) that belong to other commands in the pipeline
    // It's already ensured that the current process only has open the necessary pipe fds
    if (current->prev)
    {
        close(current->prev->fd[0]);
        close(current->prev->fd[1]);
    }
    if (current->next)
    {
        close(current->next->fd[0]);
        close(current->next->fd[1]);
    }
    
    // Close the current pipe after we're done with it
    close(current->fd[0]);
    close(current->fd[1]);
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
    execve(token->full_path, token->full_cmd, shell->env);
    ft_print_array(token->full_cmd);
    ft_free_array(token->full_cmd);
}

char    **create_cmd_tab(t_token *token)
{
    int        i;
    int        count;
    char    	**cmd;

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

int    count_for_cmd_tab(t_token *token)
{
    int        count;
    t_token    *current;

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