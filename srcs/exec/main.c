#include "minishell.h"

int	main(void)
{
	char	*rl;

	while (1)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		rl = readline("megashell >  ");
		read_line_handler(rl);
		free(rl);
	}
}
