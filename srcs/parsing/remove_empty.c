/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_empty.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:05:35 by habouda           #+#    #+#             */
/*   Updated: 2025/02/09 23:05:57 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_token_content(t_token *token)
{
	if (!token)
		return ;
	if (token->str)
		free(token->str);
	if (token->full_path)
		free(token->full_path);
	if (token->full_cmd)
		free(token->full_cmd);
	if (token->heredoc_file)
		free(token->heredoc_file);
	if (token->file_redir)
		free(token->file_redir);
	if (token->file_redir_out)
		free(token->file_redir_out);
}

static void	remove_node(t_token **head, t_token *to_delete)
{
	if (!head || !*head || !to_delete)
		return ;
	if (to_delete->prev)
		to_delete->prev->next = to_delete->next;
	else
		*head = to_delete->next;
	if (to_delete->next)
		to_delete->next->prev = to_delete->prev;
	free_token_content(to_delete);
	free(to_delete);
}

void	clean_empty_tokens(t_token **head)
{
	t_token	*current;
	t_token	*next;

	if (!head || !*head)
		return ;
	current = *head;
	while (current)
	{
		next = current->next;
		if ((!current->str || current->str[0] == '\0')
			&& current->type != EMPTY)
			remove_node(head, current);
		current = next;
	}
}
