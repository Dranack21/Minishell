#include "minishell.h"

void	print_list(t_token *head)
{
	t_token	*temp;

	if (head == NULL)
		return ;
	temp = head;
	while (temp != NULL)
	{
		printf("str value :%s", temp->str);
		printf("   type value :%d", temp->type);
		printf("   path if there's one :%s\n", temp->full_path);
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
	t_token *new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->prev = NULL;
	new_node->next = NULL;
	new_node->str = NULL;
	new_node->full_path = NULL;
	new_node->full_cmd = NULL;
	new_node->type = -1;
	return (new_node);
}
