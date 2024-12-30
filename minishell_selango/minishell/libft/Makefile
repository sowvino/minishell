NAME = libft.a

MY_SOURCES = ft_atoi.c\
			 ft_bzero.c\
			 ft_calloc.c\
			 ft_isalnum.c\
			 ft_isalpha.c\
			 ft_isascii.c\
			 ft_isdigit.c\
			 ft_isprint.c\
			 ft_itoa.c\
			 ft_memchr.c\
			 ft_memcmp.c\
			 ft_memcpy.c\
			 ft_memmove.c\
			 ft_memset.c\
			 ft_putchar_fd.c\
			 ft_putendl_fd.c\
			 ft_putnbr_fd.c\
			 ft_putstr_fd.c\
			 ft_split.c\
			 ft_strchr.c\
			 ft_strdup.c\
			 ft_striteri.c\
			 ft_strjoin.c\
			 ft_strjoin_with_sep.c\
			 ft_strlcat.c\
			 ft_strlcpy.c\
			 ft_strlen.c\
			 ft_strmapi.c\
			 ft_strncmp.c\
			 ft_strnstr.c\
			 ft_strtrim.c\
			 ft_strrchr.c\
			 ft_substr.c\
			 ft_tolower.c\
			 ft_toupper.c\
			 ft_printf.c\
			 utilis.c\
			 get_next_line.c\
			 get_next_line_utilis.c\
			
BONUS_SRCS = ft_lstnew.c\
			 ft_lstadd_front.c\
			 ft_lstsize.c\
			 ft_lstlast.c\
			 ft_lstadd_back.c\
			 ft_lstdelone.c\
			 ft_lstclear.c\
			 ft_lstiter.c\
			 ft_lstmap.c\
			 

OBJECTS = $(MY_SOURCES:.c=.o)

BONUS_OBJECTS = $(BONUS_SRCS:.c=.o)

COMPILER = cc

CFLAGS = -Wall -Wextra -Werror

INCS = libft.h\
	   ft_printf.h\
	   get_next_line.h

RM = rm -f

# Define the archiver command
LIBC = ar rcs

# Rule to build the static library
$(NAME): $(OBJECTS) $(INCS)
	$(LIBC) $(NAME) $(OBJECTS)


# Default target
all: $(NAME)

bonus: $(OBJECTS) $(BONUS_OBJECTS) $(INCS)
	$(LIBC) $(NAME) $(OBJECTS) $(BONUS_OBJECTS)

# Cleaning intermediate files
clean:
	$(RM) $(OBJECTS) $(BONUS_OBJECTS)

# Full clean, including the executable
fclean: clean
	$(RM) $(NAME)

# Rebuild everything
re: fclean all

# Phony targets (not real files)
.PHONY: all clean fclean bonus re .c .o 
