#include "minishell.h"

//check if no options before 
int ft_pwd(void)
{
    char *cwd;

    cwd = getcwd(NULL, 0);
    if (cwd = NULL)
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

int ft_echo(t_token )
{

}