#include "minishell.h"

int is_numeric(const char *str)
{
    int i;

    i = 0;
    if (str[0] == '-' || str[0] == '+')
        i++;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (EXIT_SUCCESS);
        i++;
    }
    return (EXIT_FAILURE);
}

void ft_exit(t_token *tokens)
{
    t_token     *arg;
    long long   exit_code;

    printf("exit\n");
    arg = tokens->next;
    if (!arg)
        exit(0);
    if (!is_numeric(arg->str))
    {
        printf("exit: %s: numeric argument required\n", arg->str);
        exit(255);
    }
    exit_code = ft_atol(arg->str);
    if (arg->next)
    {
        printf("exit: too many arguments\n");
        return ;
    }
    exit((unsigned char)exit_code);
}
