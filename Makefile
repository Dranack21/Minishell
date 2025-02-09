# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: habouda <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/28 01:37:02 by habouda           #+#    #+#              #
#    Updated: 2025/02/09 05:56:19 by habouda          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COMPIL #####################################################################

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
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

SRCS		= $(wildcard $(SRCS_EXEC)/*.c) \
			  $(wildcard $(SRCS_PARSING)/*.c) \
			  $(wildcard $(SRCS_LEXING)/*.c) \
			  $(wildcard $(SRCS_BUILTIN)/*.c) \
			  $(wildcard $(SRCS_UTILS)/*.c) \
			  $(wildcard $(SRCS_SIGNALS)/*.c) \
			  $(wildcard $(SRCS_FREES)/*.c) \
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
	@$(CC) $(CFLAGS) $(INCLUDES_DIRS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all re clean fclean
