#include "minishell.h"

int	parse_for_quotes(char *rl)
{
	int	counter;
	int	i;

	i = 0;
	counter = 0;
	while (rl[i])
	{
		if (rl[i] == '\'')
			counter++;
		if (rl[i] == '"')
		{
			i = skip_string_in_quotes(rl, i);
		}
		i++;
	}
	return(counter);
}
