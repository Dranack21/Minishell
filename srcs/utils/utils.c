#include "minishell.h"

int	ft_is_not_quote(char c)
{
	if (ft_isprint(c) == 0 && c != '\'' && c != '"' && ft_is_space(c) == 1)
		return (0);
	return (1);
	
}