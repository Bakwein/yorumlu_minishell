#include "../../../include/minishell.h"

char    *ft_strtonl(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '\n')
            str[i] = '\0';
        i++;
    }
    return (str);
}