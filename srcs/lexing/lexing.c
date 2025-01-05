#include "minishell.h"

// int	lexing(char *rl)
// {

// }

int	token_counter(char *rl)
{
	int i;
	int tokens;

	i = 0;
	tokens = 0;
	while (rl[i])
	{
		while (ft_is_space(rl[i]) == 1 && rl[i])
			i++;
		if (ft_isalpha(rl[i]) == 1 && rl[i])
		{
			while (ft_isalpha(rl[i]) == 1 && rl[i])
				i++;
			tokens++;
		}
		if (rl[i] == '"' && tokens++ > -1 && rl[i])
			i = skip_string_in_quotes(rl, i);
		if (rl[i] == '|' && tokens++ > -1 && rl[i])
			i++;
		if (rl[i] == '-' && tokens++ > -1 && rl[i])
			i = skip_string_in_quotes(rl, i);
	}
	return (tokens);
}

int	skip_string_in_quotes(char *rl, int i)
{
	i++;
	while (rl[i] && rl[i] != '"')
		i++;
	if (rl[i] == '"')
		i++;
	return (i);
}