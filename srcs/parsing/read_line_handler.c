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
		i++;
	}
	if (counter %2 == 1)
		return (EXIT_FAILURE);
	i = 0;
	counter = 0;
	while (rl[i])
	{
		if (rl[i] == '"')
			counter++;
		i++;
	}
	if (counter %2 == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
