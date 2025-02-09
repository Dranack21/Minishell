/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:05:10 by habouda           #+#    #+#             */
/*   Updated: 2025/02/09 23:05:57 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_special_char(t_token *token)
{
	if (ft_strcmp(token->str, "|") == 0)
		return (token->type = PIPE, 0);
	else if (ft_strcmp(token->str, ">") == 0)
		return (token->type = OUPUT, 0);
	else if (ft_strcmp(token->str, "<") == 0)
		return (token->type = INPUT, 0);
	else if (ft_strcmp(token->str, "<<") == 0)
		return (token->type = HERE_DOC, 0);
	else if (ft_strcmp(token->str, ">>") == 0)
		return (token->type = APPEND_REDIR, 0);
	return (1);
}

int	check_if_builtin(t_token *token)
{
	if (!token->str)
		return (EXIT_FAILURE);
	else if (ft_strcmp(token->str, "echo") == 0)
		return (token->type = BUILTIN, EXIT_SUCCESS);
	else if (ft_strcmp(token->str, "cd") == 0)
		return (token->type = BUILTIN, EXIT_SUCCESS);
	else if (ft_strcmp(token->str, "pwd") == 0)
		return (token->type = BUILTIN, EXIT_SUCCESS);
	else if (ft_strcmp(token->str, "export") == 0)
		return (token->type = BUILTIN, EXIT_SUCCESS);
	else if (ft_strcmp(token->str, "unset") == 0)
		return (token->type = BUILTIN, EXIT_SUCCESS);
	else if (ft_strcmp(token->str, "exit") == 0)
		return (token->type = BUILTIN, EXIT_SUCCESS);
	else if (ft_strcmp(token->str, "env") == 0)
		return (token->type = BUILTIN, EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	check_if_command(t_token *token, char *envp[])
{
	char	**paths;
	char	*full_p;
	char	*cmd_str;
	int		path;

	cmd_str = ft_strdup(token->str);
	if (access(cmd_str, X_OK) == 0)
	{
		token->full_path = ft_strdup(token->str);
		return (free(cmd_str), EXIT_SUCCESS);
	}
	path = get_path(envp);
	if (path == -1)
		return (EXIT_FAILURE);
	paths = ft_split(envp[path] + 5, ':');
	full_p = find_cmd_path(paths, cmd_str);
	if (full_p)
	{
		token->full_path = full_p;
		return (ft_free_array(paths), free(cmd_str), EXIT_SUCCESS);
	}
	ft_free_array(paths);
	free(full_p);
	free(cmd_str);
	return (EXIT_FAILURE);
}

int	check_if_export(t_token *token, char **env)
{
	int		i;
	char	*cmd_str;
	size_t	len;

	i = 0;
	if (!token || !token->str || !env)
		return (1);
	len = ft_strlen(token->str);
	if (len >= 3 && token->str[0] == '"' && token->str[1] == '$'
		&& token->str[len - 1] == '"')
		cmd_str = ft_strndup(token->str + 2, len - 3);
	else if (len >= 1 && token->str[0] == '$')
		cmd_str = ft_strdup(token->str + 1);
	else
		cmd_str = ft_strdup(token->str);
	if (!cmd_str)
		return (1);
	while (env[i])
	{
		if (ft_strncmp(env[i], cmd_str, ft_strlen(cmd_str)) == 0)
			return (token->type = CMD, free(cmd_str), 0);
		i++;
	}
	free(cmd_str);
	return (1);
}
