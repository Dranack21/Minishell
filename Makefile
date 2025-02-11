# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: habouda <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/28 01:37:02 by habouda           #+#    #+#              #
#    Updated: 2025/02/09 23:06:12 by habouda          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COMPIL #####################################################################

CC			= cc
CFLAGS = -Wall -Wextra -Werror -g -O0 -gdwarf-4
NAME 		= minishell
READLINE_FLAGS = -lreadline -ltermcap

### DIRECTORIES ################################################################

SRCS_DIR 	 = srcs
SRCS_LEXING  = $(SRCS_DIR)/lexing
SRCS_EXEC 	 = $(SRCS_DIR)/exec
SRCS_PARSING = $(SRCS_DIR)/parsing
SRCS_BUILTIN = $(SRCS_DIR)/builtin
SRCS_UTILS	 = $(SRCS_DIR)/utils
SRCS_SIGNALS = $(SRCS_DIR)/signals
SRCS_FREES 	 = $(SRCS_DIR)/frees

OBJS_DIR 	= objs
INCLUDES_DIR = includes
INCLUDES_DIRS = -I$(INCLUDES_DIR) -I$(LIBFT_DIR)

### SRC ########################################################################

SRCS		= srcs/builtin/builtin_utils.c\
				srcs/builtin/builtin.c\
				srcs/builtin/cd_builtin.c\
				srcs/builtin/echo_builtin.c\
				srcs/builtin/exit_builtin.c\
				srcs/builtin/export_builtin.c\
				srcs/builtin/unset_builtin.c\
				srcs/exec/builtins_exec.c\
				srcs/exec/cmd_tab.c\
				srcs/exec/exe_error.c\
				srcs/exec/execute.c\
				srcs/exec/no_pipes.c\
				srcs/exec/pipes.c\
				srcs/frees/frees_1.c\
				srcs/lexing/check_if_type.c\
				srcs/lexing/early_quotes.c\
				srcs/lexing/export_translator.c\
				srcs/lexing/lexing.c\
				srcs/lexing/token_counter_utils.c\
				srcs/lexing/token_counter.c\
				srcs/lexing/tokenize.c\
				srcs/parsing/apply_input_redir.c\
			  	srcs/parsing/here_doc_utils.c\
				srcs/parsing/read_line_handler.c\
				srcs/parsing/redir_input.c\
				srcs/parsing/redir_output.c\
				srcs/parsing/redir.c\
				srcs/parsing/remove_empty.c\
				srcs/parsing/synthax_parser.c\
				srcs/parsing/verifier.c\
				srcs/signals/ft_signal.c\
				srcs/signals/heredoc_signals.c\
			  	srcs/utils/builtin_utils.c\
				srcs/utils/echo_utils.c\
				srcs/utils/env_utils.c\
				srcs/utils/execute_utils.c\
				srcs/utils/heredoc_utils.c\
				srcs/utils/linked_list_utils_1.c\
				srcs/utils/pipes_utils.c\
				srcs/utils/utils.c\
			  srcs/main.c \

OBJS		= $(patsubst $(SRCS_DIR)/%, $(OBJS_DIR)/%, $(SRCS:.c=.o))

### LIBFT ######################################################################

LIBFT_DIR 	= libft
LIBFT 		= $(LIBFT_DIR)/libft.a

### RULES ######################################################################

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE_FLAGS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES_DIRS) -g -c $< -o $@


clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all re clean fclean
