#include "minishell.h"

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

int ft_echo(t_token *token, t_shell *data, char ***env)
{
    int     newline;
    t_token *current;
    int     first;

    first = 1;
    newline = 1;
    current = token->next;
    if (data->export == 1)
    {
        is_export_echo(token, env);
    } 
    if (token && strcmp(token->str, "-n") == 0)
    {
        newline = 0;
        current = token->next;
    }
    while (token)
    {
        if (!first)
            printf(" ");
        printf("%s", token->str);
        first = 0;
        current = token->next;
    }
    if (newline)
        printf("\n");
    return (EXIT_SUCCESS);
}

void    is_export_echo(t_token *token, char ***env)
{
    char    *export_value;
    char    *equal;
    t_token *current;
    int     first;

    current = token->next;
    while (token)
        {
            if (!first)
                printf(" ");
            first = 0;
            if (token->str[0] == '$')
            {
                if (search_if_export(token, env) != NULL)
                {
                    export_value = search_if_export(token, env);
                    while (export_value)
                    {
                        equal = ft_strchr(export_value, '=');
                        if (equal != 0)
                           printf("%s\n", equal + 1);
                    }
                }
            }
            else
            {
                if (!first)
                    printf(" ");
                printf("%s", token->str);
                first = 0;
            }
            current = token->next;
        }
}

char *search_if_export(t_token *token, char ***env)
{
    int i;

    i = 0;
    while ((*env)[i])
    {
        if (ft_strncmp(*env[i], token->str, ft_strlen(token->str)) == 0
         && ((*env)[i][ft_strlen(token->str)] == '=' 
         || (*env)[i][ft_strlen(token->str)] == '\0'))
         {
            return ((*env)[i]);
         }
        i++;
    }
    return (NULL);
}
