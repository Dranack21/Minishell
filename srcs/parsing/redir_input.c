#include "minishell.h"

int		prepare_redir_input(t_token *token, char **env)
{
	t_token	*current;
	t_token	*file;
	t_token	*back;
	int	i;

	i = 0;
	current = token;
	while (current)
	{
		if (current->type == HERE_DOC || current->type == INPUT)
		{
			file = current->next;
			back = find_cmd_token_redir(current, -1);
			if (!back)
				back = find_cmd_token_redir(current, 1);
			i = process_backward_heredoc(back, file, env, current);
		}
		current = current->next;
	}
	return (i);
}	

int	process_backward_heredoc(t_token *backward, t_token *file, char **env, t_token *current)
{
	int fd;

	printf("CURRENT TYPE IS %d\n", current->type);
	if (current->type == HERE_DOC)
	{
		if (process_heredoc(backward, env, file) != 0)
			return (EXIT_FAILURE);
		if (!backward)
			return (EXIT_FAILURE);
		backward->file_redir = ft_strdup(file->str);
		backward->int_redir = HERE_DOC;
	}
	if (current->type == INPUT)
	{
		fd = open(file->str, O_RDONLY);
		if (fd < 0)
			return (perror("open"), EXIT_FAILURE);
		close(fd);
		if (!backward)
			return (EXIT_FAILURE);
		backward->file_redir = ft_strdup(file->str);
		backward->int_redir = INPUT;
		backward->heredoc_file = NULL;
	}
	return (EXIT_SUCCESS);
}

int	process_heredoc(t_token *token, char **env, t_token *file)
{
	int		fd;
	char	*line;
	char	*heredoc_file;
	char	*expanded_line;
	int		status;
	pid_t	pid1;

	heredoc_file = generate_random_filename();
	fprintf(stderr, "heredoc file name : %s \n", heredoc_file);
	if (!heredoc_file)
		return (EXIT_FAILURE);
	fd = open(heredoc_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (EXIT_FAILURE);
	pid1 = fork();
	if (pid1 == 0)
	{
		ft_setup_heredoc_signals();
		while (1)
		{
			line = readline("heredoc> ");
			if (line == NULL || ft_strcmp(line, file->str) == 0)
			{
				free(line);
				break ;
			}
			expanded_line = search_if_env(line, env);
			write(fd, expanded_line, ft_strlen(expanded_line));
			write(fd, "\n", 1);	
			free(expanded_line);
		}
		exit(0);
	}	
	else
		waitpid(pid1, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	printf("status %d\n", status);
	if (status == 130)
		open(heredoc_file, O_TRUNC);
	if (token)
		token->heredoc_file = heredoc_file;
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
