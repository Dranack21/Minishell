#include "minishell.h"

void	prepare_heredoc(t_token *token)
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
				if (process_heredoc(backward) != 0)
					printf("dedge heredoc\n");
			}
		}
		current = current->next;
	}
}

int process_heredoc(t_token *token)
{
    int fd;
    char *line;
    fprintf(stderr, "heredoc file name \n");
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
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    close(fd);
    return 0;
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