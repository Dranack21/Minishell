/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:05:01 by habouda           #+#    #+#             */
/*   Updated: 2025/02/10 00:46:06 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	no_pipes(t_token *token, t_shell *shell)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->is_valid == IS_NOT_VALID && current->str != NULL)
		{
			printf("%s : command not found\n", current->str);
			current->is_valid = IS_NOT_VALID;
			shell->exit_code = 127;
			return ;
		}
		current = current->next;
	}
	current = token;
	while (current && current->type != CMD
		&& current->type != BUILTIN && current->next)
		current = current->next;
	if (current->type == CMD && current)
		cmd_wo_pipes(current, shell);
	if (current->type == BUILTIN && current)
		builtin_wo_pipes(token, shell);
}

void	builtin_wo_pipes(t_token *token, t_shell *shell)
{
	int	original_stdout;
	int	i;

	i = -1;
	original_stdout = dup(STDOUT_FILENO);
	handle_file_redirection(token);
	if (token->is_valid == IS_VALID)
	{
		i = identify_builtin_no_pipes(token, shell);
		dup2(original_stdout, STDOUT_FILENO);
		close(original_stdout);
	}
	if (i != -1)
	{
		free_exit_main(token, shell);
		exit(i);
	}
}

int	identify_builtin_no_pipes(t_token *token, t_shell *shell)
{
	int	i;

	i = -1;
	if (ft_strcmp("echo", token->str) == 0)
	{
		ft_echo(token, shell->env);
		shell->exit_code = 0;
	}
	if (ft_strcmp("pwd", token->str) == 0)
		ft_pwd(shell);
	if (ft_strcmp("cd", token->str) == 0)
		cd_builtin(shell, token, shell->env);
	if (ft_strcmp("export", token->str) == 0)
		ft_export(token, &shell->env, shell);
	if (ft_strcmp("unset", token->str) == 0)
	{
		ft_unset(token, shell->env);
		shell->exit_code = 0;
	}
	if (ft_strcmp("env", token->str) == 0)
		ft_envp(shell->env, shell);
	if (ft_strcmp("exit", token->str) == 0)
		i = ft_exit(shell, token);
	return (i);
}

void	cmd_wo_pipes(t_token *token, t_shell *shell)
{
	pid_t	pid;
	int		status;

	token->full_cmd = create_cmd_tab(token);
	if (!token->full_cmd && !token->full_path)
		return ;
	pid = fork();
	if (pid == 0)
	{
		handle_file_redirection(token);
		if (token->is_valid == IS_VALID)
		{
			if (execve(token->full_path, token->full_cmd, shell->env) == -1)
				handle_err_execve(token);
		}
		ft_free_array(token->full_cmd);
		free_exit_main(token, shell);
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_code = WEXITSTATUS(status);
	else
		shell->exit_code = status;
	ft_free_array(token->full_cmd);
}
