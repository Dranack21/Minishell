#include "minishell.h"

int	token_counter(char *str)
{
    int	i;
    int	tokens;
    int	in_token;

    i = 0;
    tokens = 0;
    while (str[i])
    {
        in_token = 0;
        i = skip_spaces(str, i);
        if (!str[i])
            break;
        if (ft_isdelim(str[i]))
        {
            tokens++;
            i = handle_double_delim(str, i);
            continue;
        }
        if (str[i])
        {
            tokens++;
            while (str[i] && !ft_isspace(str[i]) && !ft_isdelim(str[i]))
            {
                if (ft_isquote(str[i]))
                    i = process_quotes(str, i, &in_token);
                else
                {
                    in_token = 1;
                    i++;
                }
            }
        }
    }
    return (tokens);
}

int	process_quotes(char *str, int i, int *in_token)
{
    char	quote;

    quote = str[i];
    i++;
    while (str[i] && str[i] != quote)
        i++;
    if (str[i] == quote)
    {
        i++;
        if (!*in_token)
        {
            *in_token = 1;
            return (i);
        }
        while (str[i] && !ft_isspace(str[i]) && !ft_isdelim(str[i]))
        {
            if (ft_isquote(str[i]))
                i = process_quotes(str, i, in_token);
            else
                i++;
        }
    }
    return (i);
}

// Main token counting function

int	ft_isspace(char c)
{
    return (c == ' ' || c == '\t');
}

int	ft_isquote(char c)
{
    return (c == '"' || c == '\'');
}

int	ft_isdelim(char c)
{
    return (c == '>' || c == '<' || c == '|');
}

int	skip_spaces(char *str, int i)
{
    while (str[i] && ft_isspace(str[i]))
        i++;
    return (i);
}

int	handle_double_delim(char *str, int i)
{
    if (str[i] && str[i + 1] && 
        ((str[i] == '>' && str[i + 1] == '>') ||
         (str[i] == '<' && str[i + 1] == '<')))
        return (i + 2);
    return (i + 1);
}