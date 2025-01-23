#include "minishell.h"

char *strip_quotes(const char *str)
{
    char	*new_str;
    int 	len;
    int		i;
    int		j;

    len = ft_strlen(str);
    if (len >= 2 && ((str[0] == '"' && str[len - 1] == '"') ||
                     (str[0] == '\'' && str[len - 1] == '\'')))
    {
        new_str = malloc(sizeof(char) * (len - 1));
        if (!new_str)
            return (NULL);
        i = 1;
        j = 0;
        while (i < len - 1)
            new_str[j++] = str[i++];
        new_str[j] = '\0';
        return (new_str);
    }
    return (ft_strdup(str));
}
