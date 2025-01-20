#include "minishell.h"

void	prepare_redir(t_token *token)
{
    t_token *current;
    t_token *forward;
	t_token *backward;

    current = token;
    while (current)
    {
        if (current->type == OUPUT || current->type == APPEND_REDIR) 
        {
            if (current->next)
                forward = current->next;
            backward = current;
            while (backward && backward->type != CMD && backward->type != BUILTIN && backward->type != -1)
                backward = backward->prev;
            if (backward && (backward->type == CMD || backward->type == BUILTIN || backward->type == -1))
            {
                if (current->type == APPEND_REDIR)
                {
                    backward->file_redir = ft_strdup(forward->str);
                    backward->int_redir = O_APPEND;
                }
                else if (current->type == OUPUT)
                {
                    backward->file_redir = ft_strdup(forward->str);
                    backward->int_redir = O_WRONLY | O_CREAT | O_TRUNC;
                }
            }
        }
        current = current->next;
    }
}

void handle_file_redirection(t_token *cmd_token)
{
    int fd;

    if (cmd_token->int_redir != 0 && cmd_token->file_redir != NULL)
    {
        if (cmd_token->int_redir == O_APPEND)
            fd = open(cmd_token->file_redir, O_WRONLY | O_APPEND, 0644);
        else if (cmd_token->int_redir == 577)
            fd = open(cmd_token->file_redir, O_WRONLY | O_CREAT | O_TRUNC, 0644);    
        if (fd < 0)
        {
            perror("open");
            exit(1);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
}



void handle_append_redir(t_token *token)
{
    t_token *current;
    t_token *temp;

    current = token;
    while (current && current->type != APPEND_REDIR)
        current = current->next;
    if (current == NULL)
        return ;
    if (current->next)
        temp = current->next;
    while (current && current->type != CMD && current->type != BUILTIN && current->type != -1)
        current = current->prev;
    if (current && (current->type == CMD || current->type == BUILTIN || current->type == -1))
    {
        current->file_redir = ft_strdup(temp->str);
        current->int_redir = O_APPEND;
    }
}



void handle_output_redir(t_token *token)
{
    t_token *current;
    t_token *temp;

    current = token;
    while (current && current->type != OUPUT)
        current = current->next;
    if (current == NULL)
        return ;
    if (current->next)
        temp = current->next;
    while (current && current->type != CMD && current->type != BUILTIN && current->type != -1)
        current = current->prev;
    if (current && (current->type == CMD || current->type == BUILTIN || current->type == -1))
    {
        current->file_redir = ft_strdup(temp->str);
        current->int_redir = OUPUT;
    }
}


