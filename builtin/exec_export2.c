#include "builtin.h"

void ft_key_value(char *arg, char **key,char **value)
{
    size_t i;
    size_t len;

    len =ft_strlen(arg);
    i = 0;
    while (arg[i] && arg[i] != '=')
        i++;
    *key = ft_substr(arg, 0, i);
    i++;
    *value = ft_substr(arg, i, len);
}

char *ft_update(char *arg)
{
	char *key;
	char *value;
    char *update_str;
	char *tmp;

    ft_key_value(arg, &key, &value);
    if(value == NULL || value[0] == '\0')
    {
        update_str = ft_strjoin(key, "=''");
        free(value);
        free(key);
    }
    else
    {
        tmp = ft_strjoin(key, "=");
        update_str = ft_strjoin(tmp, value);
        free(tmp);
        free(value);
        free(key);
    }
    return (update_str);
}

char *ft_find_key(char *arg)
{
    size_t i;

    i = 0;
    while (arg[i] && arg[i] != '=')
        i++;
    return (ft_substr(arg, 0, i));
}