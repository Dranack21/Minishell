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

int ft_setenv(char **envp, const char *name, const char *value)
{
    int     i;
    int     len;
    int     name_len;
    int     value_len;
    char    *new_var;

    name_len = strlen(name);
    value_len = strlen(value);
    len = name_len + value_len + 2;
    new_var = malloc(len);
    if (!new_var)
        return (-1);
    i = 0;
    while (name[i])
    {
        new_var[i] = name[i];
        i++;
    }
    new_var[i] = '=';
    i++;
    len = 0;
    while (value[len])
    {
        new_var[i + len] = value[len];
        len++;
    }
    new_var[i + len] = '\0';
    i = 0;
    while (envp[i])
    {
        if (strncmp(envp[i], name, name_len) == 0 && envp[i][name_len] == '=')
        {
            free(envp[i]);
            envp[i] = new_var;
            return (0);
        }
        i++;
    }
    envp[i] = new_var;
    envp[i + 1] = NULL;
    return (0);
}

void    update_pwd_vars(char **env)
{
    char    *oldpwd;
    char    current_dir[1024];

    oldpwd = getenv("PWD");
    if (oldpwd)
        ft_setenv(env, "OLDPWD", oldpwd);
    if (getcwd(current_dir, sizeof(current_dir)))
        ft_setenv(env, "PWD", current_dir);
}

int cd_builtin(t_token *token, char **env)
{
    char    *path;
    t_token *arg;
    
    arg = token->next;
    if (!arg)
    {
        path = get_home_dir(env);
        if (!path)
        {
            printf("cd: HOME not set\n");
            return (EXIT_FAILURE);
        }
    }
    else if (strcmp(arg->str, "~") == 0)
    {
        path = get_home_dir(env);
        if (!path)
        {
            printf("cd: HOME not set\n");
            return (EXIT_FAILURE);
        }
    }
    else if (strcmp(arg->str, "-") == 0)
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
        path = arg->str;
    if (chdir(path) != 0)
    {
        perror("cd");
        return (EXIT_FAILURE);
    }
    update_pwd_vars(env);
    return (EXIT_SUCCESS);
}
