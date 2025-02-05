#include "minishell.h"

int    parse_for_quotes(char *rl)
{
    int    i;

    i = 0;
    while (rl[i])
    {
        if (rl[i] == '\'')
        {
            i++;
            while (rl[i] && rl[i] != '\'')
                i++;
            if (!rl[i])
                return (EXIT_FAILURE);
        }
        if (rl[i] == '"')
        {
            i++;
            while (rl[i] && rl[i] != '"')
                i++;
            if (!rl[i])
                return (EXIT_FAILURE);
        }
        i++;
    }
    return (EXIT_SUCCESS);
}