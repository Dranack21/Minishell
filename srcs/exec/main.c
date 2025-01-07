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
		rl = readline("salut a tous c'est mini yannick et bienvenue a mini ville>");
		if (parse_for_quotes(rl) % 2 == 1)
		{
			printf("uneven single quote go die please");
			free(rl);
			exit(0);
		}
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

