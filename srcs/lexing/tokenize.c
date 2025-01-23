#include "minishell.h"

void	get_token_type(t_token *token, char *envp[])
{
	if (token->type != -1)
		return ;
	else if (check_if_special_char(token) == 0)
		return ;
	else if (ft_strcmp(token->str, "") == 0)
		token->type = EMPTY;
	else if (check_if_builtin(token) == 0
		|| check_if_command(token, envp) == 0 || check_if_export(token,
			envp) == 0)
	{
		token = token->next;
		while (token != NULL)
		{
			if (check_if_special_char(token) == 1)
				token->type = ARG;
			else
				break ;
			token = token->next;
		}
	}
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


