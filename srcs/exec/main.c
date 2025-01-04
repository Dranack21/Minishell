#include "minishell.h"

int	main(void)
{
	loop();
	return(0);
}


void	loop()
{
	char *rl;

	ft_signal_handler();
	while (1)
	{
		rl = readline("minishell >");
		if (ft_strncmp(rl, "exit", 4) == 0)
			exit(0);
		free(rl);
	}
}