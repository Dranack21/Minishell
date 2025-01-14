#include "minishell.h"

t_token	*lexing(t_shell *shell, char *rl)
{
	int			i;
	int			debut;
	int			fin;
	t_token		*head;
	t_token		*current;

	head = NULL;
	i = token_counter(rl, 0);
	shell->token_count = i;
	printf("nombre de tokens, %d \n", i);
	while (i > 0)
	{
		ft_add_in_list_shell(&head);
		i--;
	}
	i = 0;
	current = head;
	while (rl[i])
	{
		while (ft_is_space(rl[i]) == 0 && rl[i])
			i++;
		debut = i;
		fin = token_separator(rl, i);
		if (fin == -1)
			break ;
		current->str = str_maker(rl, debut, fin);
		current = current->next;
		i = fin + 1;
	}
	return (head);
}

int	token_counter(char *rl, int i)
{
	int	tokens;

	tokens = 0;
	while (rl[i])
	{
		while (ft_is_space(rl[i]) == 0 && rl[i])
			i++;
		if (ft_is_not_quote(rl[i]) == 0 && rl[i])
		{
			while (ft_is_not_quote(rl[i]) == 0 && rl[i])
				i++;
			tokens++;
		}
		if (rl[i] == '"' && tokens++ > -1 && rl[i])
			i = skip_string_in_quotes(rl, i);
		if (rl[i] == '\'' && tokens++ > -1 && rl[i])
			i = skip_string_in_single_quotes(rl, i);
		if (rl[i] == '|' && tokens++ > -1 && rl[i])
			i++;
		if (rl[i] == '-' && tokens++ > -1 && rl[i])
		{
			while (ft_is_space(rl[i]) == 1 && rl[i])
				i++;
		}
	}
	return (tokens);
}

int	token_separator(char *rl, int i)
{
	int	tokens;

	tokens = 0;
	while (rl[i])
	{
		if (ft_is_not_quote(rl[i]) == 0 && rl[i])
		{
			while (ft_is_not_quote(rl[i]) == 0 && rl[i])
				i++;
			return (i - 1);
		}
		if (rl[i] == '"' && tokens++ > -1 && rl[i])
		{
			i = skip_string_in_quotes(rl, i);
			return (i - 1);
		}
		if (rl[i] == '\'' && tokens++ > -1 && rl[i])
		{
			i = skip_string_in_single_quotes(rl, i);
			return (i - 1);
		}
		if (rl[i] == '|' && tokens++ > -1 && rl[i])
			return (i);
		if (rl[i] == '-' && tokens++ > -1 && rl[i])
		{
			while (ft_is_space(rl[i]) == 1 && rl[i])
				i++;
			return (i - 1);
		}
	}
	return (-1);
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
