#include "minishell.h"

int	lexing(char *rl)
{
	int		i;
	int		debut;
	int		fin;
	int		tokens;
	t_token	*head;
	t_token	*current;

	i = 0;
	head = NULL;
	tokens = token_counter(rl);
	while (tokens-- >= 0)
		ft_add_in_list_shell(&head);
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

void	print_list(t_token *head)
{
	t_token	*temp;

	if (head == NULL)
		return ;
	temp = head;
	while (temp != NULL)
	{
		ft_printf("%s\n", temp->str);
		temp = temp->next;
	}
}

void	ft_lstadd_end_shell(t_token **head)
{
	t_token	*new_node;
	t_token	*temp;

	new_node = create_node_shell();
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

void	ft_add_in_list_shell(t_token **head)
{
	ft_lstadd_end_shell(head);
}

void	*create_node_shell()
{
	t_token	*new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
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

int	token_counter(char *rl)
{
	int i;
	int tokens;

	i = 0;
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

void	free_tab(t_token *head)
{
	t_token	*temp;

	while(head->next != NULL)
	{
		temp = head->next;
		free(head->str);
		free(head);
		head = temp;	
	}
}