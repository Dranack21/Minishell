/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:05:31 by habouda           #+#    #+#             */
/*   Updated: 2025/02/10 00:03:16 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prepare_redir_output(t_token *token)
{
	t_token	*current;
	t_token	*file;
	t_token	*back;
	int		i;

	i = 0;
	current = token;
	while (current)
	{
		if (current->type == OUPUT || current->type == APPEND_REDIR)
		{
			if (current->next)
				file = current->next;
			back = find_cmd_token_redir(current, -1);
			if (!back)
				back = find_cmd_token_redir(current, 1);
			i = apply_output_redirection(back, file, current);
		}
		current = current->next;
	}
	return (i);
}

int	apply_append_redirection(t_token *back, t_token *file, t_token *current)
{
	int	fd;

	if (current->type == APPEND_REDIR)
	{
		fd = open(file->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			perror(file->str);
		else
			close(fd);
		if (!back)
			return (EXIT_FAILURE);
		back->file_redir_out = ft_strdup(file->str);
		if (!back->file_redir_out)
			return (EXIT_FAILURE);
		back->int_redir_out = O_APPEND;
	}
	return (EXIT_SUCCESS);
}

int	apply_truncate_redirection(t_token *back, t_token *file, t_token *current)
{
	int	fd;

	if (current->type == OUPUT)
	{
		fd = open(file->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			perror(file->str);
		else
			close(fd);
		if (!back)
			return (EXIT_FAILURE);
		back->file_redir_out = ft_strdup(file->str);
		if (!back->file_redir_out)
			return (EXIT_FAILURE);
		back->int_redir_out = O_WRONLY | O_CREAT | O_TRUNC;
	}
	return (EXIT_SUCCESS);
}

int	apply_output_redirection(t_token *back, t_token *file, t_token *current)
{
	int	i;

	i = 0;
	if (current->type == APPEND_REDIR)
	{
		i = apply_append_redirection(back, file, current);
	}
	else if (current->type == OUPUT)
	{
		i = apply_truncate_redirection(back, file, current);
	}
	return (i);
}
