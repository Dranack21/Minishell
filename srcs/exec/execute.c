#include "minishell.h"

void    execute_main(t_shell *shell, t_token *token)
{
    shell->pipe_count = count_pipes(token);
    if (shell->pipe_count == 0)
        return ;
    else
        create_pipes(shell, token);
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
