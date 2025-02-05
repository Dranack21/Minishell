#include "../includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (0);
	shell->env = NULL;
	shell->env = copy_env(envp);
	shell->exit_code = 0;
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

	while (1)
	{
		ft_signal_handler();
		rl = readline("Minishell>");
		if (!rl)
        	break;
		add_history(rl);
		if (parse_for_quotes(rl) == EXIT_FAILURE)
		{
			printf("uneven single quote go die please\n");
		}
		else 
		{
			token = lexing(shell, rl);
			if (token != NULL)
			{
				update_all_tokens_quotes(token);
				export_traductor(token, shell->env, shell);
				token_manager(token, shell->env);
				if (synthax_parser(token) == EXIT_FAILURE)
				{
					printf("synthax error test \n ");
					free_token_tab(token);
				}
				else
				{
					prepare_redir(token);
					prepare_redir_input(token);
					prepare_heredoc(token, shell->env);
					verify_all(shell, token);
					print_list(token);
					execute_main(shell, token);
					free_token_tab(token);
				}
			}	
		}
		free(rl); 
		printf("EXIT CODEE : %d\n", shell->exit_code);
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
