/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:06:01 by habouda           #+#    #+#             */
/*   Updated: 2025/02/10 06:08:19 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_var_and_value(char *line, int i, char **env, char **value)
{
	int		j;
	int		var_len;
	char	*var_name;

	j = i + 1;
	var_len = 0;
	while (line[j] && ((line[j] >= 'A' && line[j] <= 'Z') || (line[j] >= 'a'
				&& line[j] <= 'z') || (line[j] >= '0' && line[j] <= '9')
			|| line[j] == '_'))
	{
		var_len++;
		j++;
	}
	var_name = ft_substr(line, i + 1, var_len);
	if (!var_name)
		return (NULL);
	*value = get_env_value(var_name, env);
	free(var_name);
	if (!*value)
		return (NULL);
	return (line);
}

char	*search_if_env(char *line, char **env)
{
	int		i;
	int		j;
	char	*value;
	int		var_len;

	i = position_dollar(line);
	while (i != -1)
	{
		j = i + 1;
		var_len = 0;
		while (line[j] && ((line[j] >= 'A' && line[j] <= 'Z') || (line[j] >= 'a'
					&& line[j] <= 'z') || (line[j] >= '0' && line[j] <= '9')
				|| line[j] == '_'))
		{
			var_len++;
			j++;
		}
		if (!extract_var_and_value(line, i, env, &value))
			return (line);
		line = replace_var_in_line(line, i, value, var_len);
		if (!line)
			return (NULL);
		i = position_dollar(line);
	}
	return (line);
}

char	*replace_var_in_line(char *line, int i, char *value, int var_len)
{
	char	*result;

	result = malloc(i + ft_strlen(value) + ft_strlen(line + i + var_len + 1)
			+ 1);
	if (!result)
		return (line);
	ft_strncpy(result, line, i);
	result[i] = '\0';
	ft_strcat(result, value);
	ft_strcat(result, line + i + var_len + 1);
	free(line);
	return (result);
}

int	init_heredoc(char **heredoc_file, int *fd)
{
	*heredoc_file = generate_random_filename();
	if (!*heredoc_file)
		return (EXIT_FAILURE);
	*fd = open(*heredoc_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
