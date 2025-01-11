/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 19:37:42 by habouda           #+#    #+#             */
/*   Updated: 2024/07/03 19:42:37 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*fill_line(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	line = malloc(sizeof(char) * i + 2);
	if (!line)
		return (NULL);
	ft_strlcpy(line, stash, i + 2);
	return (line);
}

static	char	*clear_stash(char *stash)
{
	int		i;
	char	*new_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\0')
	{
		new_stash = ft_strdup(&stash[i]);
		free (stash);
		stash = NULL;
		if (new_stash[0] == '\0')
		{
			free (new_stash);
			return (NULL);
		}
		return (new_stash);
	}
	else
	{
		new_stash = ft_strdup(&stash[i + 1]);
		free (stash);
		stash = NULL;
		return (new_stash);
	}
}

static char	*read_and_fill_stash(int fd, char *stash)
{
	ssize_t	bytes_read;
	char	*temp;
	char	*buffer;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!stash)
			stash = ft_strdup("");
		temp = ft_strdup(stash);
		free (stash);
		stash = ft_strjoin(temp, buffer);
		free (temp);
		temp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (free(buffer), stash);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = read_and_fill_stash(fd, stash);
	if (!stash || stash[0] == '\0')
	{
		free (stash);
		stash = NULL;
		return (NULL);
	}
	line = fill_line (stash);
	stash = clear_stash(stash);
	return (line);
}
