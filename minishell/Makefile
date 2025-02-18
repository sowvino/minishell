NAME = minishell

LIBFT = libft.a
LIBFT_PATH = libft

COMPILER = cc
CFLAGS = -Wall -Wextra -Werror -Iheaders
LFLAGS = -L$(LIBFT_PATH) -lft -lreadline

TOKENIZATION = tokenization/identifier_tokenization.c \
		 tokenization/separator_tokenization.c \
		 tokenization/tokenization_utiles.c \
		 tokenization/tokenization.c

PARSING = parsing/parser_builders.c \
	   parsing/parser_nodes.c \
	   parsing/parsing_checkers.c \
	   parsing/parsing_cleaners.c \
	   parsing/parsing_errors.c \
	   parsing/parsing_io_nodes.c \
	   parsing/parsing_utils.c \
	   parsing/parsing.c

DEFAULT_EXECUTION = default_exec/ft_cd.c \
	   default_exec/ft_echo.c \
	   default_exec/ft_exit.c \
	   default_exec/ft_export.c \
	   default_exec/ft_pwd.c \
	   default_exec/ft_unset.c \
	   default_exec/ft_utilis.c \

EXECUTION = execution/exec_utilis.c \
	   execution/execution_pipe.c \
	   execution/ft_check_permission.c \
	   execution/path_execution.c \
	   execution/redirect_execution.c \
	   execution/simple_cmd_execution.c \
	   execution/tree_init.c \

EXPANDERS = expanders/expander_quotes_handlers.c \
	   expanders/expander_utilis.c \
	   expanders/ft_expand.c \
	   expanders/ft_expander_split.c \
	   expanders/ft_remove_quotes.c \
	   expanders/ft_heredoc_expander.c \

MAIN = cleaners.c \
	environment.c \
	main.c \
	signals.c \
	utils.c

INCLUDES	=	headers/minishell.h\
				headers/parsing.h\
				headers/tokenization.h\
				headers/libft.h

SOURCES = $(TOKENIZATION) $(PARSING) $(DEFAULT_EXECUTION) $(EXECUTION) $(EXPANDERS) $(MAIN)

OBJECTS = $(SOURCES:.c=.o)

%.o: %.c
	$(COMPILER) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

$(NAME): $(OBJECTS) $(LIBFT) $(INCLUDES)
	@$(COMPILER) -o $(NAME) $(OBJECTS) $(LFLAGS)

# go: 
# 	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --show-reachable=yes --error-limit=no --suppressions=minishell.supp ./minishell

clean:
	rm -f $(OBJECTS)
	$(MAKE) clean -C $(LIBFT_PATH)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re