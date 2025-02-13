/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:06:09 by habouda           #+#    #+#             */
/*   Updated: 2025/02/13 01:43:45 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (0);
	shell->env = NULL;
	shell->env = copy_env(envp);
	shell->token = NULL;
	shell->exit_code = 0;
	if (!shell->env)
		return (0);
	(void)argc;
	(void)argv;
	loop(shell);
	ft_free_array(shell->env);
	free(shell);
	return (0);
}

void	loop(t_shell *shell)
{
	char	*rl;

	while (1)
	{
		ft_signal_handler();
		rl = readline("Minishell>");
		if (!rl)
			break ;
		add_history(rl);
		if (g_state.signal_code != 0)
		{
			shell->exit_code = g_state.signal_code;
			g_state.signal_code = 0;
		}
		if (parse_for_quotes(rl) == EXIT_FAILURE)
		{
			printf("uneven single quotes be please kind with minishell\n");
			shell->exit_code = 2;
		}
		else
			main_2(shell, rl);
		free(rl);
	}
	rl_clear_history();
}

void	main_2(t_shell *shell, char *rl)
{
	t_token	*token;

	token = lexing(shell, rl);
	shell->token = &token;
	if (token != NULL)
	{
		export_traductor(token, shell->env, shell);
		token_manager_2(token);
		update_all_tokens_quotes(token);
		new_traductor(token, shell->env, shell);
		token_manager(token, shell->env);
		clean_empty_tokens(&token);
		if (synthax_parser(token) == EXIT_FAILURE)
		{
			shell->exit_code = 2;
			free_token_tab(token);
		}
		else
		{
			prepare_redir_output(token);
			prepare_redir_input(token, shell);
			verify_all(shell, token);
			print_list(token);
			execute_main(shell, token);
		}
	}
}

void	token_manager_2(t_token *token)
{
	t_token	*current;

	if (token == NULL)
		return ;
	current = token;
	while (current != NULL)
	{
		if (current->str[0] == '\0')
			current->type = 727;
		if (current->next)
			current = current->next;
		else
			break ;
	}
}

void	token_manager(t_token *token, char *envp[])
{
	t_token	*current;

	if (token == NULL)
		return ;
	current = token;
	while (current != NULL)
	{
		get_token_type(current, envp);
		current = current->next;
	}
}
