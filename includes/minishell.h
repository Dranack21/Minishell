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
	char			**full_cmd;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;


typedef struct s_pipe
{
	int				id;
	int				fd[2];
	pid_t 			pid;
	struct s_pipe	*prev;
	struct  s_pipe	*next;
}					t_pipe;


typedef	struct s_shell
{
	int		pipe_count;
	int		token_count;
	int		export;
	char	**env;
}			t_shell;


/////// EARLY PARSING //////////////

int					parse_for_quotes(char *rl);

///////// LEXING  ///////

t_token	*lexing(t_shell *shell, char *rl);

void				get_token_type(t_token *token, char *envp[]);
void				token_manager(t_token *token, char *envp[]);

int					ft_is_not_quote(char c);
int					token_counter(char *rl, int i);
int					token_separator(char *rl, int i);

int					skip_string_in_quotes(char *rl, int i);
int					skip_string_in_single_quotes(char *rl, int i);
int					get_path(char *envp[]);

char				*find_cmd_path(char **paths, char *cmd);

//// LEXING CHECKERS ///////

int					check_if_builtin(t_token *token);
int					check_if_command(t_token *token, char *envp[]);
int					check_if_command_ACT2(char *str, char **envp);
int					check_if_export(t_token *token, char **env);
int					check_if_special_char(t_token *token);

//////// TOKEN TAB MAKER //////////

void				ft_lstadd_end_shell(t_token **head);
void				ft_add_in_list_shell(t_token **head);
void				*create_node_shell();
void				print_list(t_token *head);
void				free_tab(t_token *head);

char				*str_maker(char *rl, int debut, int fin);

void    free_pipes(t_pipe *pipe);

/////////// EXECUTE ////////////
void				create_pipes(t_shell *shell, t_token *token);
void				redirect_exe(t_shell *shell, t_token *token, t_pipe *pipe);

int					count_pipes(t_token *token);
int					count_for_cmd_tab(t_token *token);

char				**create_cmd_tab(t_token *token);

void	execute_cmd(t_token *token, t_shell *shell, t_pipe *pipe);
void	execute_main(t_shell *shell, t_token *token);

///// LINKED LIST OF PIPES ///////
void				ft_lstadd_end_pipes(t_pipe **head);
void				ft_add_in_list_pipes(t_pipe **head);
void				*create_node_pipes();

void close_unused_pipes(t_pipe *pipe);


//////////////////SIGNAUX///////////////

void				ft_signal_handler();
void				ft_handle_sigint();
void				ft_handle_sigsegv();

void	loop(t_shell *shell);
char	**copy_env(char **envp);

#endif