#include "minishell.h"

int	ft_echo(t_token *tokens, t_shell *shell, char **env)
{
	int		print_newline;
	t_token	*current;
	int		first;
	int i;
	char	*value;

	shell->export = 1;
	print_newline = 1;
	current = tokens->next;
	i = 0;
	quote(tokens);
	if (current && is_n_arg(current->str) == 0)
	{
		print_newline = 0;
		current = current->next;
	}
	first = 1;
	while (current)
	{
		if (!first)
			printf(" ");
		if (shell->export && position_dollar(current->str) != -1)
		{;
			i = position_dollar(current->str) + 1;
			value = get_env_value(current->str + i, env);
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

int	position_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

void	quote(t_token *token)
{
	t_token	*current;

	current = token;
	while (current && current->type == ARG)
	{
		current->str = strip_quotes(current->str);
		current = current->next;
	}
}

int	is_n_arg(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] == '-')
	{
		while (arg[i] == 'n')
		{
			i++;
		}
		if (arg[i] != '\0')
			return (1);
	}
	else 
		return (1);
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
