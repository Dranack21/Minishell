#include "minishell.h"

static int	process_non_delim_token(char *str, int i, int *in_token)
{
	if (!str[i])
		return (i);
	while (str[i] && !ft_isspace(str[i]) && !ft_isdelim(str[i]))
	{
		if (ft_isquote(str[i]))
			i = process_quotes(str, i, in_token);
		else
		{
			*in_token = 1;
			i++;
		}
	}
	return (i);
}

int	token_counter(char *str)
{
	int	i;
	int	tokens;
	int	in_token;

	i = 0;
	tokens = 0;
	while (str[i])
	{
		in_token = 0;
		i = skip_spaces(str, i);
		if (!str[i])
			break ;
		if (ft_isdelim(str[i]))
		{
			tokens++;
			i = handle_double_delim(str, i);
			continue ;
		}
		if (str[i])
			tokens++;
		i = process_non_delim_token(str, i, &in_token);
	}
	return (tokens);
}

int	process_quotes(char *str, int i, int *in_token)
{
	char	quote;

	quote = str[i];
	i++;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == quote)
	{
		i++;
		if (!*in_token)
		{
			*in_token = 1;
			return (i);
		}
		while (str[i] && !ft_isspace(str[i]) && !ft_isdelim(str[i]))
		{
			if (ft_isquote(str[i]))
				i = process_quotes(str, i, in_token);
			else
				i++;
		}
	}
	return (i);
}
