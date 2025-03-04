/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:05:01 by habouda           #+#    #+#             */
/*   Updated: 2025/02/13 02:04:35 by habouda          ###   ########.fr       */
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
			write(2, current->str, ft_strlen(current->str));
			if (ft_strncmp(current->str, "/", 1) == 0)
				write(2, ": No such file or directory \n", 30);
			else
				write(2, ": command not found\n", 21);
			shell->exit_code = 127;
			return ;
		}
		current = current->next;
	}
	current = token;
	while (current && current->type != CMD && current->type != BUILTIN
		&& current->next)
		current = current->next;
	if (current && current->type == CMD)
	{
		fprintf(stderr, "%s\n", current->str);
		cmd_wo_pipes(current, shell);
	}
	if (current && current->type == BUILTIN)
	{
		fprintf(stderr, "%s\n", current->str);
		builtin_wo_pipes(current, shell);
	}
}

void	builtin_wo_pipes(t_token *token, t_shell *shell)
{
	int	original_stdout;
	int	original_stdin;
	int	i;

	i = -1;
	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	handle_file_redirection(token);
	if (token->is_valid == IS_VALID)
	{
		i = identify_builtin_no_pipes(token, shell);
		dup2(original_stdout, STDOUT_FILENO);
		dup2(original_stdin, STDIN_FILENO);
		close(original_stdout);
		close(original_stdin);
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

static void	cmd_wo_pipe2(pid_t pid, t_token *token, t_shell *shell)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_code = WEXITSTATUS(status);
	else
		shell->exit_code = status;
	ft_free_array(token->full_cmd);
}

void	cmd_wo_pipes(t_token *token, t_shell *shell)
{
	pid_t	pid;

	token->full_cmd = create_cmd_tab(token);
	ft_print_array(token->full_cmd);
	if (!token->full_cmd && !token->full_path)
		return ;
	pid = fork();
	if (pid == 0)
	{
		handle_file_redirection(token);
		if (token->is_valid == IS_VALID)
		{
			if (ft_strncmp(token->str, "/", 1) == 0)
				handle_err_execve(token);
			else if (execve(token->full_path, token->full_cmd,
					shell->env) == -1)
				handle_err_execve(token);
		}
		ft_free_array(token->full_cmd);
		free_exit_main(token, shell);
		exit(0);
	}
	cmd_wo_pipe2(pid, token, shell);
}
