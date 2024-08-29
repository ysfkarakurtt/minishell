# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/29 16:46:04 by ykarakur          #+#    #+#              #
#    Updated: 2024/08/29 16:46:08 by ykarakur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -g -Wall -Wextra -Werror
LIBS = -lreadline
SRCS = src/minishell.c \
		src/lexer/lexer.c src/lexer/lexer_text.c src/lexer/lexer_get_token.c src/lexer/lexer_utils.c \
		src/utils/utils.c src/utils/error.c src/utils/free.c src/utils/utils_extra.c \
		src/signals/signals.c \
		src/parser/parser.c src/parser/parser_utils.c src/parser/parser_get_cmd.c \
		src/parser/parser_add_content.c src/parser/parser_add_file.c src/parser/parser_add_flag.c \
		src/environments/env.c src/environments/env_utils.c src/environments/env_utils_extra.c \
		src/environments/env_utils_pro.c src/expander/expander.c src/expander/append.c \
		src/executer/execute.c \
		src/executer/execute_builtin.c src/executer/execute_utils.c src/executer/execute_utils2.c \
		src/executer/heredoc.c src/executer/multi_command.c src/executer/execute_execv.c \
		src/pathfinder/pathfinder.c \
		src/builtins/ft_echo.c src/builtins/ft_cd.c src/builtins/ft_pwd.c \
		src/builtins/ft_export.c src/builtins/ft_unset.c src/builtins/ft_env.c \
		src/builtins/ft_exit.c src/builtins/ft_export_utils.c src/utils/utils_command.c

LIBFT = libft/libft.a

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)
	@echo "\033[0;32mMinishell is ready\033[0;38m...\033[0m"

$(OBJ_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "\033[0;38mCompiling \033[0;37m$<\033[0;38m...\033[0m"

clean:
	@make clean -C libft
	@rm -f $(OBJS)
	@echo "\033[0;38mCleaning \033[0;37m$(NAME)\033[0;38m...\033[0m"

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)
	@echo "\033[0;38mDeleting \033[0;37m$(NAME)\033[0;38m...\033[0m"

re: fclean all

.PHONY: all clean fclean re
