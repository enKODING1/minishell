

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);

size_t	gnl_strlcpy(char *dest, const char *src, size_t n);
size_t	gnl_strlen(const char *s);
char	*gnl_strcat(char *dest, char *src);
char	*gnl_strdup(const char *s);
char	*gnl_strchr(const char *s, int c);
#endif