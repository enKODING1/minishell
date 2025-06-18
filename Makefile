CC = cc -g
# CFLAG = -Wall -Wextra -Werror
NAME = lexer_test

SOURCES = ./lexer/main.c
OBJECTS = $(SOURCES:.c=.o)

all:$(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAG) -o $(NAME) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAG)  -c $< -o $@
	
clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME) 

re: fclean all

.PHONY: all clean fclean re