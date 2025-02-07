#include "minishell.h"

int		prepare_heredoc(t_token *token, char **env)
{
	t_token	*current;
	t_token	*file;
	t_token	*back;

	current = token;
	while (current)
	{
		if (current->type == HERE_DOC || current->type == INPUT)
		{
			if (!current->next)
				return (EXIT_FAILURE);
			file = current->next;
			back = current;
			while (back && back->type != CMD && back->type != BUILTIN)
				back = back->prev;
			if (process_backward_heredoc(back, file, env, current) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			if (!back)
			{
				back = current;
				while (back && back->type != CMD && back->type != BUILTIN)
					back = back->next;
				if (process_backward_heredoc(back, file, env, current) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
		}
		current = current->next;
	}
	return (EXIT_SUCCESS);
}	

int	process_backward_heredoc(t_token *backward, t_token *file, char **env, t_token *current)
{
	int fd;

	printf("CURRENT TYPE IS %d\n", current->type);
	if (current->type == HERE_DOC)
	{
		if (backward && (backward->type == CMD || backward->type == BUILTIN))
		{
			backward->file_redir = ft_strdup(file->str);
			backward->int_redir = HERE_DOC;
			if (process_heredoc(backward, env) != 0)
				return (EXIT_FAILURE);
		}
	}
	if (current->type == INPUT)
	{
		fd = open(file->str, O_RDONLY);
		if (fd < 0)
		{
			perror("open");
			return (EXIT_FAILURE);
		}
		close(fd);
		if (backward)
		{
			backward->file_redir = ft_strdup(file->str);
			backward->int_redir = INPUT;
			backward->heredoc_file = NULL;
		}
	}
	return (EXIT_SUCCESS);
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

char	*search_if_env(char *line, char **env)
{
	int		i;
	char	*var_name;
	char	*value;
	int		j;
	int		var_len;
	char	*result;

	printf("Input line: %s\n", line);
	while ((i = position_dollar(line)) != -1)
	{
		printf("Dollar position: %d\n", i);
		j = i + 1;
		var_len = 0;
		while (line[j] && ((line[j] >= 'A' && line[j] <= 'Z') || (line[j] >= 'a'
					&& line[j] <= 'z') || (line[j] >= '0' && line[j] <= '9')
				|| line[j] == '_')) // for now
		{
			var_len++;
			j++;
		}
		printf("Variable length: %d\n", var_len);
		var_name = ft_substr(line, i + 1, var_len);
		if (!var_name)
			return (line);
		printf("Variable name: %s\n", var_name);
		value = get_env_value(var_name, env);
		printf("Value found: %s\n", value ? value : "NULL");
		free(var_name);
		if (!value)
			return (line);
		result = malloc(i + strlen(value) + strlen(line + i + var_len + 1) + 1);
		if (!result)
			return (line);
		ft_strncpy(result, line, i);
		result[i] = '\0';
		ft_strcat(result, value);
		ft_strcat(result, line + i + var_len + 1);
		printf("Intermediate result: %s\n", result);
		free(line);
		line = result;
	}
	printf("Final result: %s\n", line);
	return (line);
}
