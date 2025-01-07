#include "minishell.h"

int	main(void)
{
	loop();
	return(0);
}


void	loop()
{
	char	*rl;

	ft_signal_handler();
	while (1)
	{
		rl = readline("minishell>");
		add_history(rl);
		if (ft_strncmp(rl, "exit", 4) == 0)
		{
			free(rl);
			rl_clear_history();
			exit(0);
		}
		lexing(rl);
	}
	rl_clear_history();
}