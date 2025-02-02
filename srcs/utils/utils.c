#include "minishell.h"

int	ft_is_not_quote(char c)
{
	if (ft_isprint(c) == 0 && ft_is_space(c) == 1)
		return (0);
	return (1);
}

int	get_path(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp[i])
		return (-1);
	return (i);
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

int	skip_string_in_single_quotes(char *rl, int i)
{
	i++;
	while (rl[i] && rl[i] != '\'')
		i++;
	if (rl[i] == '\'')
		i++;
	return (i);
}