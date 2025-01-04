#include "minishell.h"

int	main(void)
{
	char	*rl;

	while (1)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		rl = readline("megashell >  ");
		if (ft_strlen(rl) == 4 && ft_strncmp(rl, "exit", 4) == 0)
			exit(0);
		free(rl);
	}
}
