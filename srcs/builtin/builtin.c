#include "minishell.h"

// check if no options before 
int ft_pwd(void)
{
    char *cwd;

    cwd = getcwd(NULL, 0);
    if (cwd == NULL)
    {
        perror("getcwd");
        return(EXIT_FAILURE);
    }
    printf("%s\n", cwd);
    free(cwd);
    return(EXIT_SUCCESS);
}

//check if no arguments or options before 
int ft_envp(char **envp)
{
    while(*envp)
    {
        printf("%s\n", *envp);
        envp++;
    }
    return(EXIT_SUCCESS);
}

//If export then search for var name first
int ft_echo(t_token *tokens)
{
    int newline;
    t_token *token;
    int first;

    first = 1;
    newline = 1;
    token = tokens->next; 
    if (token && strcmp(token->str, "-n") == 0)
    {
        newline = 0;
        token = token->next;
    }
    while (token)
    {
        if (!first)
            printf(" ");
        printf("%s", token->str);
        first = 0;
        token = token->next;

    }
    if (newline)
        printf("\n");
    return (0);
}