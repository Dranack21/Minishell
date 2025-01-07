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

int	parse_for_quotes(char *rl)
{
	int	counter;
	int	i;

	i = 0;
	counter = 0;
	while (rl[i])
	{
		if (rl[i] == '\'')
			counter++;
		if (rl[i] == '"')
		{
			i = skip_string_in_quotes(rl, i);
		}
		i++;
	}
	return(counter);
}
