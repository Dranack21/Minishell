#include "minishell.h"

char *get_home_dir(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], "HOME=", 5) == 0)
            return (envp[i] + 5);
        i++;
    }
    return (NULL);
}

static char *create_env_string(const char *name, const char *value)
{
    int     i = 0;
    int     len = 0;
    char    *new_var;
    
    new_var = malloc(ft_strlen(name) + ft_strlen(value) + 2);
    if (!new_var)
        return (NULL);
    while (name[i])
        new_var[len++] = name[i++];
    new_var[len++] = '=';
    i = 0;
    while (value[i])
        new_var[len++] = value[i++];
    new_var[len] = '\0';
    return (new_var);
}

static int update_existing_env(char **envp, const char *name, char *new_var)
{
    int i = 0;
    int name_len = ft_strlen(name);

    while (envp[i])
    {
        if (ft_strncmp(envp[i], name, name_len) == 0 && 
            envp[i][name_len] == '=')
        {
            free(envp[i]);
            envp[i] = new_var;
            return (1);
        }
        i++;
    }
    return (0);
}

int ft_setenv(char **envp, char *name, char *value)
{
    char *new_var;
    int  i = 0;

    new_var = create_env_string(name, value);
    if (!new_var)
        return (-1);    
    if (update_existing_env(envp, name, new_var))
        return (0);
        
    while (envp[i])
        i++;
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

static int handle_home_path(char **env, char **path)
{
    *path = get_home_dir(env);
    if (!*path)
    {
        printf("cd: HOME not set\n");
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

static int handle_oldpwd(char **path)
{
    *path = getenv("OLDPWD");
    if (!*path)
    {
        printf("cd: OLDPWD not set\n");
        return (EXIT_FAILURE);
    }
    printf("%s\n", *path);
    return (EXIT_SUCCESS);
}

static int get_cd_path(t_token *token, char **env, char **path)
{
    t_token *arg = token->next;

    if (!arg || (ft_strcmp(arg->str, "~") == 0))
        return (handle_home_path(env, path));
    else if (ft_strcmp(arg->str, "-") == 0)
        return (handle_oldpwd(path));
    *path = arg->str;
    return (EXIT_SUCCESS);
}

int cd_builtin(t_token *token, char **env)
{
    char *path;
    
    if (get_cd_path(token, env, &path) != EXIT_SUCCESS)
        return (EXIT_FAILURE);
    if (chdir(path) != 0)
    {
        perror("cd");
        return (EXIT_FAILURE);
    }
    update_pwd_vars(env);
    return (EXIT_SUCCESS);
}