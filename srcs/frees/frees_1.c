/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:05:06 by habouda           #+#    #+#             */
/*   Updated: 2025/02/10 01:47:43 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_tab(t_token *head)
{
	t_token	*temp;

	while (head)
	{
		if (head->prev)
			head = head->prev;
		else
			break ;
	}
	while (head != NULL)
	{
		temp = head->next;
		if (head->str != NULL)
			free(head->str);
		if (head->full_path != NULL)
			free(head->full_path);
		if (head->file_redir != NULL)
			free(head->file_redir);
		if (head->file_redir_out != NULL)
			free(head->file_redir_out);
		if (head->heredoc_file != NULL)
			free(head->heredoc_file);
		free(head);
		head = temp;
	}
}

void	free_exit_main(t_token *token, t_shell *shell)
{
	ft_free_array(shell->env);
	free(shell);
	while (token)
	{
		if (token->prev)
			token = token->prev;
		else
			break ;
	}
	free_token_tab(token);
}

void	free_child(t_token *token, t_shell *shell, t_pipe *pipe)
{
	ft_free_array(shell->env);
	free(shell);
	while (pipe)
	{
		if (pipe->prev)
			pipe = pipe->prev;
		else
			break ;
	}
	free_pipes(pipe);
	while (token)
	{
		if (token->prev)
			token = token->prev;
		else
			break ;
	}
	free_token_tab(token);
}

void	free_inside_heredoc(t_token *token, t_shell *shell)
{
	if (shell->env)
	{
		ft_free_array(shell->env);
	}
	token = *shell->token;
	while (token)
	{
		if (token->prev)
			token = token->prev;
		else
			break ;
	}
	free(shell);
	free_token_tab(token);
}

void	free_pipes(t_pipe *pipe)
{
	t_pipe	*temp;

	while (pipe)
	{
		temp = pipe->next;
		free(pipe);
		pipe = temp;
	}
}
