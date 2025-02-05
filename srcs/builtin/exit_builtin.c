#include "minishell.h"

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

void	ft_exit(t_token *tokens)
{
	t_token		*arg;
	int			exit_code;
	int			temp;

	printf("exit\n");
	arg = tokens->next;
	if (!arg)
		exit(5);
	if (!is_numeric(arg->str))
	{
		printf("exit: %s: numeric argument required\n", arg->str);
		exit(255);
	}
	exit_code = atoi(arg->str);
	temp = exit_code % 256;
	if (arg->next)
	{
		printf("exit: too many arguments\n");
		return ;
	}
	exit(temp);
}
