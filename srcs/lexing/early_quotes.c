#include "minishell.h"

int	is_special_token(char *str)
{
    int	i;
    int	len;

    if (!str)
        return (0);
    // Skip leading quotes if present
    i = (str[0] == '"' || str[0] == '\'') ? 1 : 0;
    // Check content length excluding quotes
    len = 0;
    while (str[i + len] && str[i + len] != str[0])
        len++;
    // Check if it's just a single special character
    if (len == 1 && (str[i] == '|' || str[i] == '<' || str[i] == '>'))
        return (1);
    // Check if it's a double special character
    if (len == 2 && str[i] == str[i + 1] && 
        (str[i] == '<' || str[i] == '>'))
        return (1);
    return (0);
}

void	update_all_tokens_quotes(t_token *token)
{
    t_token	*current;

    current = token;
    while (current)
    {
        if (!is_special_token(current->str))
            update_token_quotes(current);
        current = current->next;
    }
}

int	get_clean_size(char *str)
{
    int	i;
    int	size;

    i = 0;
    size = 0;
    while (str[i])
    {
        if (!ft_isquote(str[i]))
            size++;
        i++;
    }
    return (size);
}

char	*clean_quotes(char *str)
{
    char	*result;
    int		i;
    int		j;
    char	quote_type;

    result = malloc(sizeof(char) * (get_clean_size(str) + 1));
    if (!result)
        return (NULL);
    i = 0;
    j = 0;
    quote_type = 0;
    while (str[i])
    {
        if (ft_isquote(str[i]) && !quote_type)
            quote_type = str[i];
        else if (str[i] == quote_type)
            quote_type = 0;
        else
            result[j++] = str[i];
        i++;
    }
    result[j] = '\0';
    return (result);
}

void	update_token_quotes(t_token *token)
{
    char	*cleaned;
    char	*old_str;

    old_str = token->str;
    cleaned = clean_quotes(token->str);
    if (cleaned)
    {
        token->str = cleaned;
        free(old_str);
    }
}