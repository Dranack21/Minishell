#include "minishell.h"

t_token	*lexing(t_shell *shell, char *rl)
{
	int		i;
	int		start;
	int		end;
	int		token_count;
	t_token	*head;
	t_token	*current;

	i = 0;
	head = NULL;
	token_count = token_counter(rl, 0);
	shell->token_count = token_count;
	printf("nombre de tokens: %d\n", token_count);
	if (token_count == 0)
		return (NULL);
	while (token_count > 0)
	{
		ft_add_in_list_shell(&head);
		token_count--;
	}
	current = head;
	while (rl[i] && current)
	{
		while (ft_is_space(rl[i]) == 0)
			i++;
		start = i;
		end = token_separator(rl, i);
		if (end == -1)
			break ;
		current->str = str_maker(rl, start, end);
		i = end + 1;
		while (rl[i] && ft_is_space(rl[i]) == 0)
        {
            current->has_trailing_spaces = 1;
            i++;
        }
		current = current->next;
	}
	return (head);
}

int	token_counter(char *rl, int i)
{
	int	tokens;
	char quote_type;

	tokens = 0;
	while (rl[i])
	{
		while (rl[i] && ft_is_space(rl[i]) == 0)
			i++;
		if (!rl[i])
			break ;
		if (rl[i] && (rl[i] == '"' || rl[i] == '\''))
		{
			quote_type = rl[i];
			i++;
			while (rl[i] && rl[i] != quote_type)
                i++;
			if (rl[i] == quote_type)
				tokens++;
			continue ;
		}
		if (rl[i] && (rl[i] == '|' || rl[i] == '>' || rl[i] == '<'))
		{
			tokens++;
			i++;
			if ((rl[i - 1] == '>' || rl[i - 1] == '<') && rl[i] == rl[i - 1])
				i++;
			continue ;
		}
		if (rl[i] && ft_is_not_quote(rl[i]) == 0)
		{
			tokens++;
			while (rl[i] && ft_is_space(rl[i]) != 0
				&& ft_is_not_quote(rl[i]) == 0 && rl[i] != '|' && rl[i] != '>'
				&& rl[i] != '<')
				i++;
		}
	}
	return (tokens);
}

int	token_separator(char *rl, int i)
{
	while (ft_is_space(rl[i]) == 0)
		i++;
	if (rl[i] == '|' || rl[i] == '>' || rl[i] == '<')
	{
		if ((rl[i] == '>' || rl[i] == '<') && rl[i + 1] == rl[i])
			return (i + 1);
		return (i);
	}
	while (rl[i] && ft_is_space(rl[i]) != 0 && rl[i] != '|' && rl[i] != '>' && rl[i] != '<')
		i++;
	return (i - 1);
}

char	*str_maker(char *rl, int debut, int fin)
{
	char	*str;
	int		i;

	if (fin < debut)
		return (NULL);
	i = 0;
	str = malloc(sizeof(char) * (fin - debut + 2));
	if (!str)
		return (NULL);
	while (debut <= fin)
		str[i++] = rl[debut++];
	str[i] = '\0';
	return (str);
}
