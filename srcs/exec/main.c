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
		printf("nombre de tokens :%d\n", token_counter(rl));
		free(rl);
	}
}