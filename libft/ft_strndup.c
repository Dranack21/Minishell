#include "libft.h"

char *ft_strndup(const char *s, size_t n)
{
    char    *copy;
    size_t  i;
    size_t  len = 0;

    while (s[len] && len < n)
        len++;
    copy = (char *)malloc(len + 1);
    if (!copy)
        return (NULL);
    i = 0;
    while (i < len)
    {
        copy[i] = s[i];
        i++;
    }
    copy[i] = '\0';
    return (copy);
}
