#include "../includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (0);
	shell->env = NULL;
	shell->env = copy_env(envp);
	if (!shell->env)
		return (0);
	(void)argc;
	(void)argv;
	loop(shell);
	ft_free_array(shell->env);
	return (0);
}

void	loop(t_shell *shell)
{
	char	*rl;
	t_token	*token;

	ft_signal_handler();
	while (1)
	{
		rl = readline("Minishell>");
		add_history(rl);
		if (parse_for_quotes(rl) != 0)
		{
			printf("uneven single quote go die please\n");
			free(rl);
		}
		else if (ft_strncmp(rl, "exit", 4) == 0)
		{
			free(rl);
			ft_free_array(shell->env);
			free(shell);
			rl_clear_history();
			exit(0);
		}
		else 
		{
			token = lexing(shell, rl);
			if (token != NULL)
			{
				update_all_tokens_quotes(token);
				token_manager(token, shell->env);
				prepare_redir(token);
				prepare_redir_input(token);
				prepare_heredoc(token, shell->env);
				if (synthax_parser(token) == EXIT_FAILURE)
				{
					printf("synthax error test \n ");
					free_token_tab(token);
				}
				else
				{
					verify_all(shell, token);
					print_list(token);
					execute_main(shell, token);
					free_token_tab(token);
				}
			}	
		}
	}
	rl_clear_history();
}

void	token_manager(t_token *token, char *envp[])
{
	t_token	*current;

	current = token;
	while (current != NULL)
	{
		get_token_type(current, envp);
		if (current->next)
			current = current->next;
		else
			break;
	}
}
