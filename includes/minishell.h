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

int					parse_for_quotes(char *rl); ///check if quotes are even or not///

///////// LEXING  ///////

t_token				*lexing(t_shell *shell, char *rl);			////create t_token list and calls token manager strmaker////

void				token_manager(t_token *token, char *envp[]);	//// calls get token type on all t_tokens and prints the list of token ///
void				get_token_type(t_token *token, char *envp[]);  //// CORE OF LEXING CALLS ALL OF THE FUNCTIONS TO CHECK TOKEN TYPE/////

int					ft_is_not_quote(char c); 					///// returns 1 if not a quote returns 0 if it is////
int					token_counter(char *rl, int i); ///jsplu c le bordel///
int					token_separator(char *rl, int i); ///jsplu c le bordel///

int					skip_string_in_quotes(char *rl, int i);				
int					skip_string_in_single_quotes(char *rl, int i);

///////// LEXING CHECKERS ///////////

int					check_if_builtin(t_token *token);
int					check_if_command(t_token *token, char *envp[]);
int					check_if_export(t_token *token, char **env);
int					check_if_special_char(t_token *token);
int					get_path(char *envp[]);			////gets path////

char				*find_cmd_path(char **paths, char *cmd); ////checks if yo have a path returns null if not////

//////// TOKEN TAB MAKER //////////

void				print_list(t_token *head);				//// prints linked list of t token////
void				free_token_tab(t_token *head);			///free tabs//////

char				*str_maker(char *rl, int debut, int fin);		//jsplu//

void				close_fds_and_wait_for_childs(t_pipe *head);			//// read the function name////

///////////////////////// EXECUTE //////////////////////
void				execute_main(t_shell *shell, t_token *token);				/// redirect you from pipes to no pipes////
void				redirect_exe(t_shell *shell, t_token *token, t_pipe *pipe); /// redirects first intermediates and last commands////
void				execute_cmd(t_token *token, t_shell *shell, t_pipe *pipe); ////execute the command and free full_p/////

/////////// CMD ARRAY OF ARRAY FOR EXCVE ////////////
char				**create_cmd_tab(t_token *token);         /// create the **cmd array/////

int					count_pipes(t_token *token);				//// count of all our pipes////
int					count_for_cmd_tab(t_token *token);			//// count for the size of the malloc for our **cmd array/////
char				*strip_quotes(const char *str);				//// STRIPS QUOTES FOR PASSED ARGS ///

///// LINKED LIST OF PIPES ///////
void				ft_lstadd_end_pipes(t_pipe **head); 					///create t_pipes node/////
void				ft_add_in_list_pipes(t_pipe **head);			///create t_pipes node/////
void				*create_node_pipes();									///create t_pipes node/////
void				create_pipes(t_shell *shell, t_token *token); 	//// uses forks and calls setup pipes then redirect_exe///
void				setup_pipes(t_pipe **head, int temp); 			///uses pipe() and assigns id////
void 				close_unused_pipes(t_pipe *pipe);						///close pipes inside childs////
void    			free_pipes(t_pipe *pipe); 						///free pipes at the end ////
///// LINKED LIST SHELL ////////////
void				ft_lstadd_end_shell(t_token **head);         ///create t_shell node/////
void				ft_add_in_list_shell(t_token **head);		///create t_shell node/////
void				*create_node_shell();						///create t_shell node/////
char				**copy_env(char **envp);					//// copies env /////
//////////////////SIGNAUX///////////////

void				ft_signal_handler();
void				ft_handle_sigint();
void				ft_handle_sigsegv();

void	loop(t_shell *shell);

#endif
