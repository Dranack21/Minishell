#include "../includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;

	loop(envp);
	return (0);
}

void	loop(char *envp[])
{
	char		*rl;
	t_token		*token;

	ft_signal_handler();
	while (1)
	{
		rl = readline("Minishell>");
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
		token = lexing(rl);
		token_manager(token, envp);
	}
	rl_clear_history();
}

void	token_manager(t_token *token, char *envp[])
{
	t_token	*current;

	current = token;
	while(current != NULL)
	{
		get_token_type(current, envp);
		current = current->next;
	}
	print_list(token);
}