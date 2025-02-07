#include "minishell.h"

void	print_list(t_token *head)
{
	t_token	*temp;

	if (head == NULL)
		return ;
	temp = head;
	while (temp != NULL)
	{
		printf("str :%s |", temp->str);
		printf(" type :%d |", temp->type);
		printf(" valid ?: %d |", temp->is_valid);
		printf(" File input redir %d |", temp->int_redir);
		printf(" File output %s |", temp->file_redir_out);
		printf(" File intput %s |", temp->file_redir);
		printf(" path %s\n", temp->full_path);
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

void	*create_node_shell(void)
{
	t_token	*new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->prev = NULL;
	new_node->next = NULL;
	new_node->str = NULL;
	new_node->full_path = NULL;
	new_node->full_cmd = NULL;
	new_node->heredoc_file = NULL;
	new_node->file_redir = NULL;
	new_node->file_redir_out = NULL;
	new_node->type = -2;
	new_node->has_trailing_spaces = 0;
	new_node->is_valid = IS_VALID;
	new_node->int_redir = 0;
	new_node->int_redir_out = 0;
	new_node->quote_type = 0;
	return (new_node);
}
