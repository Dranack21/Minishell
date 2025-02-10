/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synthax_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:05:37 by habouda           #+#    #+#             */
/*   Updated: 2025/02/10 05:52:46 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	synthax_parser(t_token *token)
{
	if (check_pipes_parser(token) == EXIT_FAILURE)
	{
		printf("synthax error please be kind with minishell\n ");
		return (EXIT_FAILURE);
	}
	if (check_for_redirs_parser(token) == EXIT_FAILURE)
	{
		printf("synthax error please be kind with minishell\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	check_for_redirs_parser(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (is_redir(current) == EXIT_SUCCESS && current->next)
		{
			if (is_redir(current->next) == EXIT_SUCCESS)
				return (EXIT_FAILURE);
		}
		current = current->next;
	}
	current = token;
	while (current->next)
		current = current->next;
	if (current && is_redir(current) == EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	is_redir(t_token *current)
{
	if (current && (current->type == HERE_DOC || current->type == OUPUT
			|| current->type == INPUT || current->type == APPEND_REDIR))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	check_pipes_parser(t_token *token)
{
	t_token	*currt;

	currt = token;
	if (currt && currt->type == PIPE)
		return (EXIT_FAILURE);
	while (currt)
	{
		if (currt->type == PIPE && currt->next)
		{
			if (currt->next && currt->next->type == PIPE)
				return (EXIT_FAILURE);
		}
		if (is_redir(currt) == EXIT_SUCCESS)
		{
			if (!currt->next || (currt->next && currt->next->type == PIPE))
				return (EXIT_FAILURE);
		}
		currt = currt->next;
	}
	currt = token;
	while (currt->next)
		currt = currt->next;
	if (currt && currt->type == PIPE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_token	*check_pipe_line(t_token *token)
{
	t_token	*current;
	int		cmd;

	cmd = 0;
	current = token;
	if (!current)
		return (NULL);
	while (current && current->type != PIPE)
	{
		if (current->type == CMD || current->type == BUILTIN)
			cmd = 1;
		if (current->type == ARG)
		{
			if (cmd == 0)
				return (current);
		}
		current = current->next;
	}
	if (!current)
		current = token;
	return (current);
}
