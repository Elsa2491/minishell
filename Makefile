NAME = minishell

CC = cc -Wall -Wextra -Werror
MAKEFLAGS += --no-print-directory

GREEN := \e[32m
RESET :=\e[0m

LIBFT =	includes/libft
FT_LIBFT = includes/libft/libft.a

PRINTF = includes/printf
FT_PRINTF = includes/printf/libftprintf.a

GNL = includes/get_next_line/get_next_line.c
GNL_UTILS = includes/get_next_line/get_next_line_utils.c

SRCS_PATH = $(shell find srcs -type d)

SRCS = ft_echo.c ft_env.c ft_export.c ft_export_utils.c ft_export_utils_bis.c ft_unset.c ft_exit.c ft_exit_utils.c ft_cd.c ft_cd_utils.c ft_pwd.c \
		clean.c singletons.c \
		cmds.c cmd_args.c lst_cmds.c lst_cmds_bis.c redir_cmds.c redir_cmds_bis.c \
		get_env.c lst_env.c \
		error_handle.c \
		expand.c expand_utils.c expand_utils_bis.c expand_utils_tri.c\
		tokenization.c lst_token.c check_syntax.c parsing_utils.c parsing_utils_2.c \
		signals.c signals_bis.c signals_hd.c add_tokens.c \
		get_path.c handle_access.c handle_errors.c handle_execve_error.c handle_duplications.c handle_path.c \
		handle_pipes.c handle_one_cmd.c free_functions.c \
		handle_processes.c here_doc.c here_doc_error.c exec.c \
		print_errors.c size_functions.c split.c string_functions.c wait_and_close.c \
		handle_built_in.c handle_redir.c handle_redir_utils.c \
		init_minish.c main.c 
	
vpath %.c $(foreach dir, $(SRCS_PATH), $(dir):)

OBJS_PATH = objs/

OBJS = $(addprefix $(OBJS_PATH), $(SRCS:%.c=%.o))

all: $(NAME)

$(OBJS_PATH)%.o: %.c
	@mkdir -p $(OBJS_PATH)
	$(CC) -c $< -o $@

$(NAME): $(OBJS)
	@echo "\nCompilation minishell: $(GREEN)success$(RESET)\n"
	make $(MAKEFLAGS) -C "./includes/printf"
	make $(MAKEFLAGS) -C "./includes/libft"
	$(CC) $(OBJS) -Inc $(FT_PRINTF) -Inc $(FT_LIBFT) -Inc $(GNL) -Inc $(GNL_UTILS) -lreadline -o $(NAME)

clean:
	/bin/rm -rf $(OBJS)
	@echo "\nMinishell removed: $(GREEN)success$(RESET)\n"
	make clean -C $(LIBFT) && make clean -C $(PRINTF) 

fclean:	clean
	/bin/rm -rf ${NAME}
	make fclean -C $(LIBFT) && make fclean -C $(PRINTF)

re: fclean all

.PHONY: all clean fclean re
