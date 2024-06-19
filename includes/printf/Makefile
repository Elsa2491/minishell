NAME = libftprintf.a
CFLAGS = -Wall -Wextra -Werror
SRCS_PATH = srcs/
OBJS_PATH = objs/
SRCS = ft_printf.c ft_print_address.c \

OBJS = $(SRCS:.c=.o)
SRC = $(addprefix $(SRCS_PATH), $(SRCS))
OBJ = $(addprefix $(OBJS_PATH), $(OBJS))

all: $(NAME)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	cc $(CFLAGS) -c $< -o $@

$(OBJ): $(OBJS_PATH)
$(OBJS_PATH):
	@mkdir $(OBJS_PATH)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)


clean:
	/bin/rm -rf $(OBJ)
	/bin/rm -rf $(OBJS_PATH)

fclean: clean
	/bin/rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

