#include "minishell.h"

void prepare_heredoc(t_token *token, char **env)
{
	t_token *current;
	t_token *file;
	t_token *backward;

	current = token;
	while (current)
	{
		if (current->type == HERE_DOC)
		{
			if (!current->next)
				return;
			file = current->next;
			backward = current;
			while (backward && backward->type != CMD
				&& backward->type != BUILTIN && backward->type != -1)
				backward = backward->prev;
			if (backward && (backward->type == CMD || backward->type == BUILTIN 
				|| backward->type == -1))
			{
				backward->file_redir = ft_strdup(file->str);
				backward->int_redir = HERE_DOC;
				if (process_heredoc(backward, env) != 0)
					printf("dedge heredoc\n");
			}
		}
		current = current->next;
	}
}

int process_heredoc(t_token *token, char **env)
{
    int fd;
    char *line;
	char *expanded_line;

	token->heredoc_file = generate_random_filename();
    fprintf(stderr, "heredoc file name : %s \n", token->heredoc_file);
	if (!token->heredoc_file)
		return -1;
    fd = open(token->heredoc_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) 
        return -1;
    while (1)
    {
        line = readline("heredoc> ");
        if (line == NULL || ft_strcmp(line, token->file_redir) == 0)
        {
            free(line);
            break;
        }
		expanded_line = search_if_env(line, env);
        write(fd, expanded_line, ft_strlen(expanded_line));
		write(fd, "\n", 1);
		free(expanded_line); 
    }
    close(fd);
    return 0;
}
char *search_if_env(char *line, char **env)
{
    int     i;
    char    *var_name;
    char    *value;
    int     j;
    int     var_len;
    char    *result;

    printf("Input line: %s\n", line);
    while ((i = position_dollar(line)) != -1)
    {
        printf("Dollar position: %d\n", i);
        j = i + 1;
        var_len = 0;
        while (line[j] && ((line[j] >= 'A' && line[j] <= 'Z') || 
                           (line[j] >= 'a' && line[j] <= 'z') || 
                           (line[j] >= '0' && line[j] <= '9') || 
                           line[j] == '_')) //for now
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

char	*generate_random_filename(void)
{
	char	*filename;
	int		i;

	filename = (char *)malloc(sizeof(char) * (RAND_LEN + 15));
	if (!filename)
		return (NULL);
	i = 0;
	while (HEREDOC_PREFIX[i])
	{
		filename[i] = HEREDOC_PREFIX[i];
		i++;
	}
	while (i < RAND_LEN + 14)
	{
		filename[i] = ft_rand_char();
		i++;
	}
	filename[i] = '\0';
	if (access(filename, F_OK) == 0)
	{
		free(filename);
		return (generate_random_filename()); 
	}
	return (filename);
}

int	ft_rand_char(void)
{
	int		fd;
	char	c;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		return ('a'); 
	if (read(fd, &c, 1) != 1)
	{
		close(fd);
		return ('a');
	}
	close(fd);
	return ('a' + (c % 26)); 
}

char *ft_strcat(char *dst, const char *src)
{
    size_t i;
    size_t j;

    i = 0;
    while (dst[i])
        i++;
    j = 0;
    while (src[j])
    {
        dst[i + j] = src[j];
        j++;
    }
    dst[i + j] = '\0';
    return (dst);
}

char *ft_strncpy(char *dst, const char *src, size_t len)
{
    size_t i;

    i = 0;
    while (i < len && src[i])
    {
        dst[i] = src[i];
        i++;
    }
    while (i < len)
    {
        dst[i] = '\0';
        i++;
    }
    return (dst);
}