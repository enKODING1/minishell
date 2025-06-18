CC = cc -g
# CFLAG = -Wall -Wextra -Werror
NAME = test

SOURCES = ./lexer/lexer_test.c
OBJECTS = $(SOURCES:.c=.o)

LIBFT_DIR = ./lib/libft/
LEXER_DIR = ./lexer/
TOKEN_DIR = ./token/
LIBFT_LIB = ${LIBFT_DIR}/libft.a

all:$(NAME)

$(NAME): $(LIBFT_LIB) $(OBJECTS) 
	$(CC) $(CFLAG) -o $(NAME) $(OBJECTS) \
	-I${LIBFT_DIR} -I${TOKEN_DIR} -I{LEXER_DIR} \
	-L${LIBFT_DIR} -lft

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)
	make bonus -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAG)  -c $< -o $@ \
	-I${LIBFT_DIR} -I${LEXER_DIR} -I${TOKEN_DIR} 
	
clean:
	make clean -C $(LIBFT_DIR)
	rm -f $(OBJECTS) 

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME) 

re: fclean all

.PHONY: all clean fclean re