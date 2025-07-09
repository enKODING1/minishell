CC = cc -g
# CFLAG = -Wall -Wextra -Werror
NAME = test

VPATH = ./executor ./builtin ./lexer ./parser

# lexer test
# SOURCES = ./lexer/test/lexer_test.c \
           ./lexer/lexer.c \
           ./lexer/utils/token_handler.c \
           ./lexer/utils/redirection_handler.c \
           ./lexer/utils/read.c \
           ./lexer/utils/utils.c \
           ./lexer/utils/free.c 

# parser test
# SOURCES = ./lexer/lexer.c \
			    ./lexer/utils/utils.c \
          ./lexer/utils/token_handler.c \
          ./lexer/utils/redirection_handler.c \
          ./lexer/utils/read.c \
          ./lexer/utils/free.c \
          ./parser/test/parser_test.c \
          ./parser/utils/token_to_list.c \
          ./parser/utils/print_ast.c \
          ./parser/utils/ast_utils.c \
          ./parser/parse/cmd.c \
          ./parser/parse/pipe.c \
          ./parser/parse/redirection.c 

# executor test
SOURCES = ./lexer/lexer.c \
			    ./lexer/utils/utils.c \
          ./lexer/utils/token_handler.c \
          ./lexer/utils/redirection_handler.c \
          ./lexer/utils/read.c \
          ./lexer/utils/free.c \
          ./parser/utils/token_to_list.c \
          ./parser/utils/print_ast.c \
          ./parser/utils/ast_utils.c \
          ./parser/parse/cmd.c \
          ./parser/parse/pipe.c \
          ./parser/parse/redirection.c \
          ./executor/executor_env.c \
          ./executor/executor_cmd.c \
          ./executor/executor_redir.c \
          ./executor/executor_pipe.c \
          ./executor/executor_signal.c \
          ./executor/executor.c \
          ./builtin/builtin_util.c \
          ./builtin/exec_cd.c \
          ./builtin/exec_echo.c \
          ./builtin/exec_env.c \
          ./builtin/exec_error.c \
          ./builtin/exec_exit.c \
          ./builtin/exec_export.c \
          ./builtin/exec_pwd.c \
          ./builtin/exec_unset.c \
          ./builtin/echo_util.c \
          ./builtin/exec_export2.c \
          ./builtin/string_builder.c \

OBJECTS = $(SOURCES:.c=.o)

LIBFT_DIR = ./lib/libft/
LEXER_DIR = ./lexer/
TOKEN_DIR = ./token/
PARSER_DIR = ./parser/
BUILTIN_DIR = ./builtin/
EXEC_TESTER_DIR = ./exec/


LIBFT_LIB = ${LIBFT_DIR}/libft.a

all:$(NAME)

$(NAME): $(LIBFT_LIB) $(OBJECTS) 
	$(CC) $(CFLAG) -o $(NAME) $(OBJECTS) \
	-I${LIBFT_DIR} -I${TOKEN_DIR} -I${LEXER_DIR} -I${PARSER_DIR} -I${BUILTIN_DIR} -I${EXEC_TESTER_DIR} \
	-L${LIBFT_DIR} -lft -lreadline

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)
	make bonus -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAG)  -c $< -o $@ \
	-I${LIBFT_DIR} -I${LEXER_DIR} -I${TOKEN_DIR}  -I${PARSER_DIR} -I${BUILTIN_DIR} -I${EXEC_TESTER_DIR}
	
clean:
	make clean -C $(LIBFT_DIR)
	rm -f $(OBJECTS) 

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME) 

re: fclean all

.PHONY: all clean fclean re