

#ifndef CM_READLINE_H
# define CM_READLINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

char	*cm_readline(int fd);

size_t	cm_strlcpy(char *dest, const char *src, size_t n);
size_t	cm_strlen(const char *s);
char	*cm_strcat(char *dest, char *src);
char	*cm_strdup(const char *s);
char	*cm_strchr(const char *s, int c);
#endif