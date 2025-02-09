/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:04:55 by habouda           #+#    #+#             */
/*   Updated: 2025/02/09 23:05:57 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_cmd_tab(t_token *token)
{
	int		i;
	char	**cmd;

	i = 0;
	cmd = malloc(sizeof(char *) * (count_for_cmd_tab(token) + 1));
	if (!cmd)
		return (NULL);
	while (token)
	{
		if (token->type == CMD || token->type == BUILTIN)
		{
			cmd[i++] = strip_quotes(token->str);
			token = token->next;
			while (token && token->type != PIPE)
			{
				if (token->type == ARG || token->type == 0)
					cmd[i++] = strip_quotes(token->str);
				token = token->next;
			}
			break ;
		}
		token = token->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

int	count_for_cmd_tab(t_token *token)
{
	int		count;
	t_token	*current;

	current = token;
	count = 0;
	while (current)
	{
		if (current->type == CMD || current->type == BUILTIN)
		{
			count++;
			current = current->next;
			while (current && current->type != PIPE)
			{
				if (current->type == ARG || current->type == 0)
					count++;
				current = current->next;
			}
			break ;
		}
		current = current->next;
	}
	return (count);
}
