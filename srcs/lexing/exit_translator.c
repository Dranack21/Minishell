#include "minishell.h"

static void	process_str_expansion(char *str, char *expanded, char *exit_str,
		int *j)
{
	int	in_quote;
	int	i;

	i = -1;
	in_quote = 0;
	while (str[++(i)])
	{
		if (str[i] == '\'')
			in_quote = !in_quote;
		if (!in_quote && str[i] == '$' && str[i + 1] == '?')
			handle_exit_var(expanded, exit_str, &i, j);
		else
		{
			expanded[*j] = str[i];
			expanded[*j + 1] = '\0';
			(*j)++;
		}
	}
}

char	*expand_exit_new(char *str, int exit_status, int quote_type)
{
	int		i;
	int		j;
	char	*expanded;
	char	*exit_str;

	i = -1;
	j = 0;
	expanded = malloc(exit_new_length(str, exit_status) + 3);
	if (!expanded)
		return (NULL);
	exit_str = ft_itoa(exit_status);
	if (!exit_str)
		return (free(expanded), NULL);
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] == '?' && quote_type != 1)
			handle_exit_var(expanded, exit_str, &i, &j);
		else
		{
			expanded[j] = str[i];
			expanded[j + 1] = '\0';
			j++;
		}
	}
	return (free(exit_str), expanded[j] = '\0', expanded);
}

int	exit_new_length(char *str, int exit_status)
{
	int	len;
	int	i;
	int	exit_len;

	len = 0;
	i = 0;
	exit_len = get_exit_str_len(exit_status);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			len += exit_len;
			i++;
		}
		else
			len++;
		i++;
	}
	return (len);
}

char	*expand_exit_status(char *str, int exit_status)
{
	int		j;
	char	*expanded;
	char	*exit_str;

	j = 0;
	expanded = malloc(exit_expanded_length(str, exit_status) + 1);
	if (!expanded)
		return (NULL);
	exit_str = ft_itoa(exit_status);
	if (!exit_str)
		return (free(expanded), NULL);
	expanded[0] = '\0';
	process_str_expansion(str, expanded, exit_str, &j);
	return (free(exit_str), expanded[j] = '\0', expanded);
}

int	exit_expanded_length(char *str, int exit_status)
{
	int	len;
	int	i;
	int	in_quote;
	int	exit_len;

	len = 0;
	i = 0;
	in_quote = 0;
	exit_len = get_exit_str_len(exit_status);
	while (str[i])
	{
		if (str[i] == '\'')
			in_quote = !in_quote;
		if (str[i] == '$' && str[i + 1] == '?' && !in_quote)
		{
			len += exit_len;
			i++;
		}
		else
			len++;
		i++;
	}
	return (len);
}
