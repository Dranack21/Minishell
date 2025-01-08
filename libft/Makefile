# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: habouda <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/28 01:37:02 by Habouda           #+#    #+#              #
#    Updated: 2025/01/04 18:56:32 by habouda          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COMPIL #####################################################################

CC	= cc
CFLAGS	= -Wall -Wextra -Werror
NAME = libft.a

### SRC ########################################################################

SRCS	=	ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_strtrim.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_substr.c \
		ft_putchar_fd.c \
		ft_toupper.c \
		ft_strjoin.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_striteri.c \
		ft_strmapi.c \
		ft_itoa.c \
		ft_putstr_fd.c \
		ft_strjoin.c \
		ft_putendl_fd.c \
		ft_split.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_memchr.c \
		ft_strdup.c \
		ft_memcmp.c \
		ft_putnbr_fd.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_printf.c \
		ft_printf_utils.c \
		ft_printf_utils2.c \
		ft_get_next_line.c \
		ft_atol.c \
		ft_is_space.c \
		ft_atof.c \
		ft_is_digit_or_float.c \
		ft_free_array.c \
		ft_count_words.c \

SRCS_BONUS	=	ft_lstnew_bonus.c \
				ft_lstadd_front_bonus.c \
				ft_lstsize_bonus.c \
				ft_lstlast_bonus.c \
				ft_lstadd_back_bonus.c \
				ft_lstdelone_bonus.c \
				ft_lstclear_bonus.c \
				ft_lstiter_bonus.c \
				ft_lstmap_bonus.c \

### OBJS ###########################################################################
			
OBJS	= $(SRCS:.c=.o)
OBJS_BONUS	= $(SRCS_BONUS:.c=.o)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
### COMMANDS #######################################################################

all: $(NAME)  

$(NAME): $(OBJS) 
		ar rcs $(NAME) $(OBJS)
		@rm -f $(OBJS)

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean:	clean
	rm -f $(NAME)

re : fclean all

bonus :  $(OBJS) $(OBJS_BONUS) 
		ar rcs $(NAME) $(OBJS) $(OBJS_BONUS)


.PHONY : all re fclean clean bonus


