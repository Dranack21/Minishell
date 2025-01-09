#include "minishell.h"

void	get_token_type(t_token *token, char *envp[])
{
	if (ft_strcmp(token->str, "") == 0)
		token->type = EMPTY;
	else if (ft_strcmp(token->str, "|") == 0)
		token->type = PIPE;
	else if (check_if_builtin(token->str) == 0)
		token->type = BUILTIN;
	else if (ft_strcmp(token->str, ">") == 0)
		token->type	= OUPUT;
	else if (ft_strcmp(token->str, "<") == 0)
		token->type	= INPUT;
	else if (ft_strcmp(token->str, "<<") == 0)
		token->type = HERE_DOC;
	else if (ft_strcmp(token->str, ">>") == 0)
		token->type = APPEND_REDIR;
	else if (check_if_command(token , envp) == 0)
		token->type = CMD;
}

int		check_if_builtin(char *str)
{
	if (!str)
		return (EXIT_FAILURE);
	else if (ft_strcmp(str, "echo") == 0)
		return (EXIT_SUCCESS);
	else if (ft_strcmp(str, "cd") == 0)
		return (EXIT_SUCCESS);
	else if (ft_strcmp(str, "pwd") == 0)
		return (EXIT_SUCCESS);
	else if (ft_strcmp(str, "export") == 0)
		return (EXIT_SUCCESS);
	else if (ft_strcmp(str, "unset") == 0)
		return (EXIT_SUCCESS);
	else if (ft_strcmp(str, "exit") == 0)
		return (EXIT_SUCCESS);
	else if (ft_strcmp(str, "env") == 0)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	check_if_command(t_token *token, char *envp[])
{
	char	**paths;
	char	*full_p;
	char	*cmd_str;
	
	if (token->str[0] == '"' && token->str[ft_strlen(token->str) - 1] == '"')
		cmd_str = ft_strndup(token->str + 1, ft_strlen(token->str) - 2);
	else
		cmd_str = ft_strdup(token->str);
	if (access(cmd_str, X_OK) == 0)
	{
		free(cmd_str);
		return (EXIT_SUCCESS);
	}
	paths = ft_split(envp[get_path(envp)] + 5, ':');
	full_p = find_cmd_path(paths, cmd_str);
	if (full_p)
	{
		token->full_path = full_p;
		ft_free_array(paths);
		free(cmd_str);
		return (EXIT_SUCCESS);
	}
	ft_free_array(paths);
	free(full_p);
	free(cmd_str);
	return (EXIT_FAILURE);
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


