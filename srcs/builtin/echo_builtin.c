#include "minishell.h"

int	ft_echo(t_token *tokens, t_shell *shell, char **env)
{
	int		print_newline;
	t_token	*current;
	int		first;
	char	*value;

	shell->export = 1;
	print_newline = 1;
	current = tokens->next;
	if (current && ft_strcmp(current->str, "-n") == 0)
	{
		print_newline = 0;
		current = current->next;
	}
	first = 1;
	while (current && current->type == ARG)
	{
		if (!first)
			printf(" ");
		if (shell->export && current->str[0] == '$')
		{
			value = get_env_value(current->str + 1, env);
			if (value)
				printf("%s", value);
			else
				printf("%s", current->str);
		}
		else
			printf("%s", current->str);
		first = 0;
		current = current->next;
	}
	if (print_newline)
		printf("\n");
	return (0);
}

char	*get_env_value(char *var_name, char **env)
{
	char	*env_var;
	int		i;
	int		len;

	if (!var_name || var_name[0] == '\0')
		return (NULL);
	len = 0;
	while (var_name[len] && var_name[len] != '=')
		len++;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, len) == 0 && env[i][len] == '=')
		{
			env_var = env[i] + len + 1;
			return (env_var);
		}
		i++;
	}
	return (NULL);
}
