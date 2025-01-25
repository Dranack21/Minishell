#include "minishell.h"

void	get_token_type(t_token *token, char *envp[])
{
	if (token->type != -2) 
		return;
	if (check_if_special_char(token) == 0 && token->type != PIPE)
	{
		if (token->next)
			token->next->type = -1;
	}
	else if (ft_strcmp(token->str, "") == 0)
		token->type = EMPTY;
	else if (check_if_builtin(token) == 0)
		token->type = BUILTIN;
	else if (check_if_command(token, envp) == 0)
		token->type = CMD;
	else if (check_if_export(token, envp) == 0)
		token->type = CMD;
	else if (ft_strcmp(token->str, "|") == 0)
		token->type = PIPE;
	else
		token->type = ARG;
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


