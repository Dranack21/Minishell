#include "minishell.h"

int is_valid_identifier(char *str)
{
    int i;

    if (!str || !*str || ft_isdigit(*str))
        return (EXIT_SUCCESS);
    i = 0;
    while (str[i])
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (0);
        i++;
    }
    return (EXIT_FAILURE);
}

char *get_var_name(char *str)
{
    int i;
    char *name;

    i = 0;
    while (str[i] && str[i] != '=')
        i++;
    name = ft_strndup(str, i);
    return (name);
}

void update_env_var(char ***env, char *var)
{
    int i;
    char *name;
    char **new_env;

    name = get_var_name(var);
    i = 0;
    while ((*env)[i])
    {
        if (ft_strncmp((*env)[i], name, ft_strlen(name)) == 0 
            && ((*env)[i][ft_strlen(name)] == '=' 
            || (*env)[i][ft_strlen(name)] == '\0'))
        {
            free((*env)[i]);
            (*env)[i] = ft_strdup(var);
            free(name);
            return;
        }
        i++;
    }
    new_env = malloc(sizeof(char *) * (i + 2));
    if (!new_env)
    {
        free(name);
        return;
    }
    i = 0;
    while ((*env)[i])
    {
        new_env[i] = ft_strdup((*env)[i]);
        i++;
    }
    new_env[i] = ft_strdup(var);
    new_env[i + 1] = NULL;
    ft_free_array(*env);
    *env = new_env;
    free(name);
}

int ft_export(char **args, char ***env, t_shell *data)
{
    int i;
    char *name;

    data->export = 1;
    if (!args[1])
        return (0);
    i = 1;
    while (args[i])
    {
        if (ft_strchr(args[i], '='))
        {
            name = get_var_name(args[i]);
            if (is_valid_identifier(name))
                update_env_var(env, args[i]);
            else
            {
                printf("no, write better %s\n", args[i]);
            }
            free(name);
        }
        i++;
    }
    return (EXIT_SUCCESS);
}
