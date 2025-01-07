#include "minishell.h"

int	ft_is_not_quote(char c)
{
	if (ft_isprint(c) == 1 && c != '\'' && c != '"' && ft_is_space(c) == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
	
}