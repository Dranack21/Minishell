#include "minishell.h"

void	get_token_type(t_token *token, char *envp[])
{
	if (token->type != -2) 
		return;
	if (check_if_special_char(token) == 0 && token->type != PIPE)
	{
		if (token->next && check_if_special_char(token->next) == 1)
			token->next->type = -1;
	}
	else if (ft_strcmp(token->str, "") == 0)
		token->type = EMPTY;
	else if (check_if_builtin(token) == 0)
		token->type = BUILTIN;
	else if (check_if_command(token, envp) == 0 && check_if_command_before(token) == 0)
		token->type = CMD;
	else if (ft_strcmp(token->str, "|") == 0)
		token->type = PIPE;
	else
		token->type = ARG;
}

int		check_if_path(t_token *token)
{
	struct stat	stats;

	if (stat(token->str, &stats) == 0)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
	
}

int		check_if_command_before(t_token	*token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->type == PIPE)
			break;
		if (current->type == CMD || current->type == BUILTIN)
			return (1);
		if (current->prev)
			current = current->prev;
		else
			break;
	}
	return (0);
}
char	*find_cmd_path(char **paths, char *cmd)
{
	char	*temp;
	char	*full_p;
	int		i;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_p = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_p, X_OK) == 0)
			return (full_p);
		free(full_p);
		i++;
	}
	return (NULL);
}
