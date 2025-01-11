#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

////// TOKENS //////////////

# define EMPTY 0
# define CMD 1
# define BUILTIN 2
# define ARG 3
# define HERE_DOC 4
# define APPEND_REDIR 5
# define INPUT 6
# define OUPUT 7
# define PIPE 8
# define END 9

typedef struct s_token
{
	char			*str;
	char			*full_path;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

/////// EARLY PARSING //////////////

int					parse_for_quotes(char *rl);

///////// LEXING  ///////

void				get_token_type(t_token *token, char *envp[]);

int					ft_is_not_quote(char c);
int					token_counter(char *rl, int i);
int					token_separator(char *rl, int i);
int					skip_string_in_quotes(char *rl, int i);
int					skip_string_in_single_quotes(char *rl, int i);
int					check_if_builtin(char *str);
int					check_if_command(t_token *token, char *envp[]);
int					get_path(char *envp[]);
int					check_if_special_char(t_token *token);

char				*find_cmd_path(char **paths, char *cmd);
void				token_manager(t_token *token, char *envp[]);

t_token				*lexing(char *rl);

int	check_if_command_ACT2(char *str, char **envp);
int		check_if_export(t_token *token, char **env);
//////// TOKEN TAB MAKER //////////

void				ft_lstadd_end_shell(t_token **head);
void				ft_add_in_list_shell(t_token **head);
void				*create_node_shell();
void				print_list(t_token *head);
void				free_tab(t_token *head);

char				*str_maker(char *rl, int debut, int fin);

//////////////////SIGNAUX///////////////

void				ft_signal_handler();
void				ft_handle_sigint();
void				ft_handle_sigsegv();

void	loop(char *envp[]);
char	**copy_env(char **envp);

#endif