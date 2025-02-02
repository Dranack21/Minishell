#include "minishell.h"

void	token_traductor(t_token *token, char *envp[])
{
	t_token *current;
	t_token	*temp;

	current = token;
	while (current)
	{
		temp = malloc(sizeof(t_token));
		temp->str = truncate_quotes(current->str);
		printf("before translation: %s\n after translation: %s\n", current->str, temp->str);
		if (check_if_command(temp, envp) == EXIT_SUCCESS || check_if_builtin(temp) == 0)
			current->str = ft_strdup(temp->str);
		free(temp->str);
		free(temp);
		if (current->next)
			current = current->next;
		else
			break;
	}
}
char* truncate_quotes(const char *str) 
{
    char *result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = (char*)malloc(strlen(str) + 1);
    if (result == NULL)
	{
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    while (str[i])
	{
        if (str[i] != '"' && str[i] != '\'')
            result[j++] = str[i];
        i++;
    }
    result[j] = '\0';
    return (result);
}
