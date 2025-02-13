/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:05:17 by habouda           #+#    #+#             */
/*   Updated: 2025/02/13 01:42:28 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexing(t_shell *shell, char *rl)
{
	int		i;
	t_token	*head;
	t_token	*current;
	int		end;

	head = NULL;
	i = 0;
	token_add_list(rl, shell, &head);
	current = head;
	while (current && rl[i])
	{
		i = skip_spaces(rl, i);
		if (!rl[i])
			break ;
		if (ft_isdelim(rl[i]))
			i = handle_delim_token(rl, i, current);
		else
		{
			end = get_token_end(rl, i);
			current->str = extract_token(rl, i, end);
			i = end;
		}
		current = current->next;
	}
	return (head);
}

char	*extract_token(char *str, int start, int end)
{
	char	*token;
	int		i;

	token = malloc(sizeof(char) * (end - start + 1));
	if (!token)
		return (NULL);
	i = 0;
	while (start < end)
		token[i++] = str[start++];
	token[i] = '\0';
	return (token);
}

int	get_token_end(char *str, int i)
{
	char	quote;

	while (str[i] && !ft_isspace(str[i]) && !ft_isdelim(str[i]))
	{
		if (ft_isquote(str[i]))
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
			if (str[i])
				i++;
		}
		else
			i++;
	}
	return (i);
}

int	handle_delim_token(char *str, int i, t_token *current)
{
	char	delim[3];
	int		j;

	j = 0;
	delim[j++] = str[i++];
	if (str[i] && str[i - 1] == str[i] && (str[i] == '>' || str[i] == '<'))
		delim[j++] = str[i++];
	delim[j] = '\0';
	current->str = ft_strdup(delim);
	return (i);
}

void	token_add_list(char *rl, t_shell *shell, t_token **head)
{
	int	temp;

	shell->token_count = token_counter(rl);
	temp = shell->token_count;
	while (temp > 0)
	{
		ft_add_in_list_shell(head);
		temp--;
	}
}
