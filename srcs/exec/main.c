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
		lexing(rl);
		free(rl);
	}
}