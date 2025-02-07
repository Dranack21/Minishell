#include "minishell.h"

void	prepare_heredoc(t_token *token, char **env)
{
	t_token	*current;
	t_token	*file;
	t_token	*back;

	current = token;
	while (current)
	{
		if (current->type == HERE_DOC)
		{
			if (!current->next)
				return ;
			file = current->next;
			back = current;
			while (back && back->type != CMD && back->type != BUILTIN)
				back = back->prev;
			process_backward_heredoc(back, file, env);
			if (!back)
			{
				while (back && back->type != CMD && back->type != BUILTIN)
					back = back->next;
				process_backward_heredoc(back, file, env);
			}
		}
		current = current->next;
	}
}

int	process_heredoc(t_token *token, char **env)
{
	int		fd;
	char	*line;
	char	*expanded_line;

	ft_setup_heredoc_signals();
	token->heredoc_file = generate_random_filename();
	fprintf(stderr, "heredoc file name : %s \n", token->heredoc_file);
	if (!token->heredoc_file)
		return (-1);
	fd = open(token->heredoc_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	while (1)
	{
		line = readline("heredoc> ");
		if (line == NULL || ft_strcmp(line, token->file_redir) == 0)
		{
			free(line);
			break ;
		}
		expanded_line = search_if_env(line, env);
		write(fd, expanded_line, ft_strlen(expanded_line));
		write(fd, "\n", 1);
		free(expanded_line);
	}
	return (close(fd), ft_restore_signals(), 0);
}

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

	result = malloc(i + strlen(value) + strlen(line + i + var_len + 1) + 1);
	if (!result)
		return (line);
	ft_strncpy(result, line, i);
	result[i] = '\0';
	ft_strcat(result, value);
	ft_strcat(result, line + i + var_len + 1);
	free(line);
	return (result);
}
