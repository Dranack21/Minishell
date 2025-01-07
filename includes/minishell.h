/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:02:37 by habouda           #+#    #+#             */
/*   Updated: 2025/01/07 19:42:48 by habouda          ###   ########.fr       */
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

/////// EARLY PARSING //////////////

int	parse_for_quotes(char *rl);




///////// TOKENS ///////

int	lexing(char *rl);
int	token_counter(char *rl, int i);
int	token_separator(char *rl, int i);
int	skip_string_in_quotes(char *rl, int i);
int	skip_string_in_single_quotes(char *rl, int i);

//////// TOKEN TAB MAKER //////////

void	ft_lstadd_end_shell(t_token **head);
void	ft_add_in_list_shell(t_token **head);
void	*create_node_shell();
void	print_list(t_token *head);
void	free_tab(t_token *head);

char	*str_maker(char *rl, int debut, int fin);



//////////////////SIGNAUX///////////////

void	ft_signal_handler(void);
void	ft_handle_sigint();
void	ft_handle_sigsegv();



void	loop();

#endif