NAME = minishell

SRCDIRS = src src/analizer src/execute src/execute/builtins src/display src/files \
src/initialize src/main src/get_next_line src/history src/free src/llist
OBJDIR = obj
LIBFTDIR = libft

# Find all .c files in the source directories
SRC_FILES = $(wildcard $(addsuffix /*.c,$(SRCDIRS)))
OBJ_FILES = $(patsubst %.c,$(OBJDIR)/%.o,$(SRC_FILES))

LIBFT = $(LIBFTDIR)/libft.a
INCLUDES = -I./include -I$(LIBFTDIR)/include

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L$(LIBFTDIR) -lft_printf -lreadline -lhistory #-lncurses
RM = rm -rf

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(OBJDIR) $(OBJ_FILES)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ_FILES) $(LDFLAGS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)  # Create the necessary directories for object files
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBFT):
	make -C $(LIBFTDIR)

clean:
	$(RM) $(OBJDIR)
	make -C $(LIBFTDIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFTDIR) fclean

re: fclean all
