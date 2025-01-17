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
    
    // Create all pipes before forking
    current = head;
    while (current != NULL)
    {
        if (pipe(current->fd) == -1)
        {
            perror("pipe");
            exit(1);
        }
        current->id = i++;
        current = current->next;
    }

    // Fork processes
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

    // Close all pipes in parent
    current = head;
    while (current != NULL)
    {
        close(current->fd[0]);
        close(current->fd[1]);
        current = current->next;
    }

    // Wait for all children
    current = head;
    while (current != NULL)
    {
        waitpid(current->pid, NULL, 0);
        current = current->next;
    }
}

void redirect_exe(t_shell *shell, t_token *token, t_pipe *pipe)
{
    t_pipe *current = pipe;
    
    // Close all pipes except the ones we need
    while (current != NULL)
    {
        if (current != pipe && (pipe->id == 0 || current != pipe->prev))
        {
            close(current->fd[0]);
            close(current->fd[1]);
        }
        current = current->next;
    }

    // First process (j'ai peur)
    if (pipe->id == 0)
    {
        close(pipe->fd[0]);  // Close read end of first pipe
        dup2(pipe->fd[1], STDOUT_FILENO);
        close(pipe->fd[1]);
    }
    // Last process (wc -l)
    else if (pipe->id == shell->pipe_count)
    {
        close(pipe->prev->fd[1]);  // Close write end of previous pipe
        dup2(pipe->prev->fd[0], STDIN_FILENO);
        close(pipe->prev->fd[0]);
    }
    // Middle process (ls -l)
    else
    {
        close(pipe->fd[0]);  // Close read end of current pipe
        close(pipe->prev->fd[1]);  // Close write end of previous pipe
        
        dup2(pipe->prev->fd[0], STDIN_FILENO);  // Read from previous pipe
        dup2(pipe->fd[1], STDOUT_FILENO);       // Write to current pipe
        
        close(pipe->prev->fd[0]);  // Close original fds after dup2
        close(pipe->fd[1]);
    }

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