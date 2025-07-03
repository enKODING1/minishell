NAME = edgeshell

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ../lib/libft
EXEC_DIR = ../exec

INCLUDES = -I$(LIBFT_DIR) -I$(EXEC_DIR) -I.

SRCS =  main.c \
        builtin_util.c \
        exec_cd.c \
        exec_echo.c \
        exec_env.c \
        exec_error.c \
        exec_exit.c \
        exec_export.c \
        exec_pwd.c \
        exec_unset.c \
        sig.c \
        main_util.c

OBJS = $(SRCS:.c=.o)

LIBFT = $(LIBFT_DIR)/libft.a
LIBS = -L$(LIBFT_DIR) -lft -lreadline

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re