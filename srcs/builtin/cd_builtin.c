#include "minishell.h"

char *get_home_dir(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        if (strncmp(envp[i], "HOME=", 5) == 0)
            return (envp[i] + 5);
        i++;
    }
    return (NULL);
}

void    update_pwd_vars(char **envp)
{
    char    *oldpwd;
    char    *pwd;
    char    current_dir[1024];

    oldpwd = getenv("PWD");
    if (oldpwd)
        setenv("OLDPWD", oldpwd, 1);
    if (getcwd(current_dir, sizeof(current_dir)))
        setenv("PWD", current_dir, 1);
}

int cd_builtin(char **args, char **envp)
{
    char    *path;
    
    if (!args[1])
    {
        path = get_home_dir(envp);
        if (!path)
        {
            printf("cd: HOME not set\n");
            return (EXIT_FAILURE);
        }
    }
    else if (strcmp(args[1], "~") == 0)
    {
        path = get_home_dir(envp);
        if (!path)
        {
            printf("cd: HOME not set\n");
            return (EXIT_FAILURE);
        }
    }
    else if (strcmp(args[1], "-") == 0)
    {
        path = getenv("OLDPWD");
        if (!path)
        {
            printf("cd: OLDPWD not set\n");
            return (EXIT_FAILURE);
        }
        printf("%s\n", path);
    }
    else
        path = args[1];
    if (chdir(path) != 0)
    {
        perror("cd");
        return (EXIT_FAILURE);
    }
    update_pwd_vars(envp);
    return (EXIT_SUCCESS);
}