#include "minishell.h"

char    **create_cmd_tab(t_token *token)
{
    int        i;
    int        count;
    char    	**cmd;

    count = count_for_cmd_tab(token);
    i = 0;
    cmd = malloc(sizeof(char*) * (count + 1));
    if (!cmd)
        return (NULL);
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