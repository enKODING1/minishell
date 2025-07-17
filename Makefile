CC = cc -g
# CFLAG = -Wall -Wextra -Werror
NAME = test

VPATH = ./executor ./builtin ./lexer ./parser

# Common source files
COMMON_SOURCES = ./lexer/lexer.c \
          ./lexer/utils/utils.c \
          ./lexer/utils/token_handler.c \
          ./lexer/utils/token_word_handler.c \
          ./lexer/utils/redirection_handler.c \
          ./lexer/utils/read.c \
          ./lexer/utils/free.c

# lexer test sources
LEXER_SOURCES = $(COMMON_SOURCES) \
          ./lexer/test/lexer_test.c

# parser test sources  
PARSER_SOURCES = $(COMMON_SOURCES) \
          ./parser/test/parser_test.c \
          ./parser/utils/token_to_list.c \
          ./parser/utils/print_ast.c \
          ./parser/utils/ast_utils.c \
          ./parser/utils/free_ast.c \
          ./parser/utils/free.c \
          ./parser/parse/cmd.c \
          ./parser/parse/pipe.c \
          ./parser/parse/redirection.c

# executor test sources
EXECUTOR_SOURCES = $(COMMON_SOURCES) \
          ./parser/utils/token_to_list.c \
          ./parser/utils/print_ast.c \
          ./parser/utils/ast_utils.c \
          ./parser/utils/free_ast.c \
          ./parser/utils/free.c \
          ./parser/parse/cmd.c \
          ./parser/parse/pipe.c \
          ./parser/parse/redirection.c \
          ./executor/executor_env.c \
          ./executor/executor_cmd.c \
          ./executor/executor_redir.c \
          ./executor/executor_heredoc.c \
          ./executor/executor_heredoc_expand.c \
          ./executor/executor_pipe.c \
          ./executor/executor_pipe_utils.c \
          ./executor/executor_pipe_children.c \
          ./executor/executor_utils.c \
          ./executor/executor_signal.c \
          ./executor/executor_signal2.c \
          ./executor/executor.c \
          ./executor/get_cmd_path.c \
          ./executor/run_command.c \
          ./builtin/builtin_util.c \
          ./builtin/builtin_util2.c \
          ./builtin/exec_cd.c \
          ./builtin/exec_cd2.c \
          ./builtin/exec_echo.c \
          ./builtin/exec_env.c \
          ./builtin/exec_error.c \
          ./builtin/exec_exit.c \
          ./builtin/exec_export.c \
          ./builtin/exec_export2.c \
          ./builtin/exec_export3.c \
          ./builtin/exec_pwd.c \
          ./builtin/exec_unset.c \
          ./builtin/exec_unset2.c \
          ./lib/readline/cm_readline.c \
          ./lib/readline/cm_readline_utils.c \
          ./builtin/echo_util.c \
          ./builtin/echo_util2.c \
          ./builtin/string_builder.c

# Default to executor sources
SOURCES = $(EXECUTOR_SOURCES)
OBJECTS = $(SOURCES:.c=.o)

LIBFT_DIR = ./lib/libft/
LEXER_DIR = ./lexer/
TOKEN_DIR = ./token/
PARSER_DIR = ./parser/
BUILTIN_DIR = ./builtin/
EXEC_TESTER_DIR = ./exec/
GNL_DIR = ./lib/readline/


LIBFT_LIB = ${LIBFT_DIR}/libft.a

all: $(NAME)

help:
	@echo "Available targets:"
	@echo "  all       - Build executor (default)"
	@echo "  lexer     - Build lexer test program"
	@echo "  parser    - Build parser test program"  
	@echo "  executor  - Build executor (same as all)"
	@echo "  clean     - Remove object files"
	@echo "  fclean    - Remove object files and executables"
	@echo "  re        - Rebuild all"
	@echo "  help      - Show this help message"



# Lexer test target
lexer: 
	$(MAKE) lexer_test

lexer_test: $(LIBFT_LIB) $(LEXER_SOURCES:.c=.o)
	$(CC) $(CFLAG) -o lexer_test $(LEXER_SOURCES:.c=.o) \
	-I${LIBFT_DIR} -I${TOKEN_DIR} -I${LEXER_DIR} -I${PARSER_DIR} -I${BUILTIN_DIR} -I${EXEC_TESTER_DIR} -I${GNL_DIR} \
	-L${LIBFT_DIR} -lft -lreadline

# Parser test target
parser:
	$(MAKE) parser_test

parser_test: $(LIBFT_LIB) $(PARSER_SOURCES:.c=.o)
	$(CC) $(CFLAG) -o parser_test $(PARSER_SOURCES:.c=.o) \
	-I${LIBFT_DIR} -I${TOKEN_DIR} -I${LEXER_DIR} -I${PARSER_DIR} -I${BUILTIN_DIR} -I${EXEC_TESTER_DIR} -I${GNL_DIR} \
	-L${LIBFT_DIR} -lft -lreadline

# Executor test target
executor:
	$(MAKE) $(NAME)

$(NAME): $(LIBFT_LIB) $(EXECUTOR_SOURCES:.c=.o)
	$(CC) $(CFLAG) -o $(NAME) $(EXECUTOR_SOURCES:.c=.o) \
	-I${LIBFT_DIR} -I${TOKEN_DIR} -I${LEXER_DIR} -I${PARSER_DIR} -I${BUILTIN_DIR} -I${EXEC_TESTER_DIR} -I${GNL_DIR} \
	-L${LIBFT_DIR} -lft -lreadline

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)
	make bonus -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAG)  -c $< -o $@ \
	-I${LIBFT_DIR} -I${LEXER_DIR} -I${TOKEN_DIR}  -I${PARSER_DIR} -I${BUILTIN_DIR} -I${EXEC_TESTER_DIR} -I${GNL_DIR}
	
clean:
	make clean -C $(LIBFT_DIR)
	rm -f $(OBJECTS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME) lexer_test parser_test

re: fclean all

.PHONY: all clean fclean re lexer parser executor lexer_test parser_test help