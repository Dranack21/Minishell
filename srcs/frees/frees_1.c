#include "minishell.h"


//// FREE DU TABLEAU DE TOKEN LORS DE SA CREATION ET ASSIGNATION DE CHAQUE STR ///////


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