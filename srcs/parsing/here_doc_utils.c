/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:05:25 by habouda           #+#    #+#             */
/*   Updated: 2025/02/09 23:05:57 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*ft_strcat(char *dst, const char *src)
{
	size_t	i;
	size_t	j;

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

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

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
