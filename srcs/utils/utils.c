#include "minishell.h"

int	ft_is_not_quote(char c)
{
	if (ft_isprint(c) == 0 && c != '\'' && c != '"' && ft_is_space(c) == 1)
		return (0);
	return (1);
}

int	get_path(char *envp[])
{
	int	i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	return (i);
}