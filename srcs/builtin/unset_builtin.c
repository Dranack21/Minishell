#include "minishell.h"

int ft_unset(t_token *tokens, char **env)
{
    t_token *current;
    int i;
    int j;
    int len;

    current = tokens->next;
    while (current)
    {
        i = 0;
        while (env[i])
        {
            len = ft_strlen(current->str);
            if (ft_strncmp(env[i], current->str, len) == 0 && env[i][len] == '=')
            {
                j = i - 1;
                while (env[++j])
                    env[j] = env[j + 1];
                break;
            }
            i++;
        }
        current = current->next;
    }
    return (EXIT_SUCCESS);
}
