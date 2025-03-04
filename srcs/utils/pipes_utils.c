/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:06:06 by habouda           #+#    #+#             */
/*   Updated: 2025/02/09 23:06:07 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes(t_token *token)
{
	int		i;
	t_token	*current;

	i = 0;
	current = token;
	while (current != NULL)
	{
		if (current->type == PIPE)
			i++;
		current = current->next;
	}
	return (i);
}

void	ft_lstadd_end_pipes(t_pipe **head)
{
	t_pipe	*new_node;
	t_pipe	*temp;

	new_node = create_node_pipes();
	if (!head || !new_node)
		return ;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	else
	{
		temp = *head;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = new_node;
		new_node->prev = temp;
	}
}

void	ft_add_in_list_pipes(t_pipe **head)
{
	ft_lstadd_end_pipes(head);
}

void	close_unused_pipes(t_pipe *pipe)
{
	t_pipe	*current;

	current = pipe;
	while (current->prev)
		current = current->prev;
	while (current->next)
	{
		close(current->fd[0]);
		close(current->fd[1]);
		current = current->next;
	}
}

void	*create_node_pipes(void)
{
	t_pipe	*new_node;

	new_node = (t_pipe *)malloc(sizeof(t_pipe));
	if (!new_node)
		return (NULL);
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}
