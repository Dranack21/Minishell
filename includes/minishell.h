/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:02:37 by habouda           #+#    #+#             */
/*   Updated: 2025/01/05 20:22:14 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>


////// TOKENS //////////////

# define CMD 1 
# define ARG 2
# define PIPE 3


typedef struct	s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

///////// TOKENS ///////

int	token_counter(char *rl);
int	skip_string_in_quotes(char *rl, int i);


//////////////////SIGNAUX///////////////

void	ft_signal_handler(void);
void	ft_handle_sigint();
void	ft_handle_sigsegv();



void	loop();

#endif