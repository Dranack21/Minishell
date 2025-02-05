#include "minishell.h"

char	**copy_env(char **envp)
{
	char	**env;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	env = malloc((i + 1) * sizeof(char *));
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
		{
			while (i--)
				free(env[i]);
			free(env);
			return (NULL);
		}
		i++;
	}
	env[i] = NULL;
	return (env);
}

int	get_path(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp[i])
		return (-1);
	return (i);
}
