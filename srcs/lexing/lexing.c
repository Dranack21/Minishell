#include "minishell.h"

int	lexing(char *rl)
{
	int		i;
	int		debut;
	int		fin;
	t_token	*head;
	t_token	*current;

	head = NULL;
	i = token_counter(rl, 0);
	while (i-- >= 0)
		ft_add_in_list_shell(&head);
	i = 0;
	current = head;
	while (rl[i])
	{
		while (ft_is_space(rl[i]) == 1 && rl[i])
			i++;
		debut = i;
		fin = token_separator(rl, i);
		i = fin;
		head->str = str_maker(rl, debut, fin);
		head = head->next;
		i++;
	}
	print_list(current);
	free_tab(head);
	return (0);
}

char *str_maker(char *rl, int debut, int fin)
{
    char *str;
    int i;

    i = 0;
    str = malloc(sizeof(char) * (fin - debut + 1));
    if (!str)
        return (NULL);
    while (debut <= fin)
        str[i++] = rl[debut++];
    str[i] = '\0'; 
    return (str);
}

int	token_counter(char *rl, int i)
{
	int tokens;

	tokens = 0;
	while (rl[i])
	{
		while (ft_is_space(rl[i]) == 1 && rl[i])
			i++;
		if (ft_isalpha(rl[i]) == 1 && rl[i])
		{
			while (ft_isalpha(rl[i]) == 1 && rl[i])
				i++;
			tokens++;
		}
		if (rl[i] == '"' && tokens++ > -1 && rl[i])
			i = skip_string_in_quotes(rl, i);
		if (rl[i] == '|' && tokens++ > -1 && rl[i])
			i++;
		if (rl[i] == '-' && tokens++ > -1 && rl[i])
		{
			while (ft_is_space(rl[i]) == 0 && rl[i])
				i++;
		}
	}
	return (tokens);
}

int	token_separator(char *rl, int i)
{
	int tokens;

	tokens = 0;
	while (rl[i])
	{
		if (ft_isalpha(rl[i]) == 1 && rl[i])
		{
			while (ft_isalpha(rl[i]) == 1 && rl[i])
				i++;
			return (i - 1);
		}
		if (rl[i] == '"' && tokens++ > -1 && rl[i])
		{
			i = skip_string_in_quotes(rl, i);
				return (i - 1);
		}
		if (rl[i] == '|' && tokens++ > -1 && rl[i])
			return (i++);
		if (rl[i] == '-' && tokens++ > -1 && rl[i])
		{
			while (ft_is_space(rl[i]) == 0 && rl[i])
				i++;
			return (i - 1);
		}
	}
	return (0);
}

int	skip_string_in_quotes(char *rl, int i)
{
	i++;
	while (rl[i] && rl[i] != '"')
		i++;
	if (rl[i] == '"')
		i++;
	return (i);
}
