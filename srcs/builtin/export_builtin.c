#include "minishell.h"

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str || !ft_isdigit(*str))
		return (1);
	i = 0;
	while (str[i])
	{
		if (!str[i])
			return (0);
		if (ft_isalpha(str[i]) == 1 || str[i] == '_')
			return (1);
		i++;
	}
	return (0);
}

char	*get_var_name(char *str)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=' && str[i - 1])
		name = ft_strndup(str, i);
	else
		return (NULL);
	return (name);
}

void	update_env_var(char ***env, char *var)
{
	int		i;
	char	*name;
	char	**new_env;

	name = get_var_name(var);
	if (!name)
		return;
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


int	ft_export(t_token *token, char ***env, t_shell *data)
{
	char	*name;

	if (!token || !token->next)
		return (handle_export_issue(token, env, data), 0);
	token = token->next;
	name = get_var_name(token->str);
	if (name == NULL)
	{
		if (token->next)
			token = token->next;
		printf("export: `%s': not a valid identifier \n", token->str);
		return (data->exit_code = 1, EXIT_FAILURE);
	}
	while (token)
	{
		if (is_valid_identifier(name) == 0)
			update_env_var(env, token->str); 
		else
		{
			printf("no, write better %s\n", token->str);
			data->exit_code = 1;
		}
		token = token->next; 
	}
	return (free(name), EXIT_SUCCESS);
}

void	handle_export_issue(t_token *token, char ***env, t_shell *data)
{
	char	**env_copy;
	int		i;

	i = 0;
	if (token && !token->next)
	{
		env_copy = copy_env(*env);
		if (!env_copy)
		{
			data->exit_code = 1;
			return ;
		}
		while (env_copy[i])
		{
			printf("export ");
			printf("%s\n", env_copy[i]);
			free(env_copy[i]);
			i++;
		}
		free(env_copy);
		data->exit_code = 0;
	}
}
