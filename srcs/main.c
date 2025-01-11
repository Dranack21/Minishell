#include "../includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	**env;
	int		i;

	i = 0;
	env = copy_env(envp);
	if (!env)
		return (0);
	while(env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	(void)argc;
	(void)argv;

	loop(env);
	ft_free_array(env);
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

char	**copy_env(char **envp)
{
	char	**env;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	env = malloc((i + 1) * sizeof(char *));
	if (!env)
		return(NULL);
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
		{
			while (i--)
				free(env[i]);
			free(env);
			return(NULL);
		}
		i++;
	}
	env[i] = NULL;
	return (env);
}
