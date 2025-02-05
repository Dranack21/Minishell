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
# include <errno.h>
# include <unistd.h>
# include <sys/stat.h> 
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
# define PATH 10

# define IS_VALID 0
# define IS_NOT_VALID 1

#define HEREDOC_PREFIX "/tmp/.heredoc_"
#define RAND_LEN 8

typedef struct s_token
{
	char			*str;
	char			*full_path;
	char			**full_cmd;
	int				type;
	int				int_redir;
	char			*file_redir;
	int				quote_type;
	int				is_valid;
	int				has_trailing_spaces;
	char			*heredoc_file;
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
	int		exit_code;
	int		pipe_count;
	int		token_count;
	int		export;
	char	**env;
}			t_shell;

void    loop(t_shell *shell);
/////// EARLY PARSING //////////////

int					parse_for_quotes(char *rl); ///check if quotes are even or not///


////////// SYNTHAX CHECKER ////////////
int					synthax_parser(t_token *token);
int					check_pipes_parser(t_token *token);
int					check_for_redirs_parser(t_token *token);
int					is_redir(t_token *current);
////////// BIG ASS PARSING ////////////////
void				verify_all(t_shell *shell, t_token *token);
void				verify_for_pipes(t_token *token);
void				verify_for_no_pipes(t_token	*token);
int					pipeline_destroyer(t_token	*token);
///////// LEXING  ///////
t_token				*lexing(t_shell *shell, char *rl);			
char				*extract_token(char *str, int start, int end);
int					get_token_end(char *str, int i);
int					handle_delim_token(char *str, int i, t_token *current);
void				token_add_list(char *rl , t_shell *shell, t_token **head);
/////// REMOVE QUOTES //////////////
void				update_all_tokens_quotes(t_token *token);
void				update_token_quotes(t_token *token);
int					get_clean_size(char *str);
char				*clean_quotes(char *str);
int					is_special_token(char *str);

///////// TOKEN TYPE ///////////
void				token_manager(t_token *token, char *envp[]);	//// calls get token type on all t_tokens and prints the list of token ///
void				get_token_type(t_token *token, char *envp[]);  //// CORE OF LEXING CALLS ALL OF THE FUNCTIONS TO CHECK TOKEN TYPE/////
int					skip_string_in_quotes(char *rl, int i);				
int					skip_string_in_single_quotes(char *rl, int i);


//////////////UTILS///////////////
int				handle_exit_code(t_token *token, t_shell *shell);
void				export_traductor(t_token *token, char *envp[], t_shell *shell);
char 				*process_dollar_string(char *str, char **env, int quote_type);
int 				calculate_expanded_length(char *str, char **env);
///////// TOKEN COUNTER////////
int					token_counter(char *rl);
int					process_quotes(char *str, int i, int *in_token);
int					ft_isspace(char c);
int					ft_isquote(char c);
int					ft_isdelim(char c);
int					skip_spaces(char *str, int i);
int					handle_double_delim(char *str, int i);
///////// LEXING CHECKERS ///////////

int					check_if_command_before(t_token	*token);
int					check_if_builtin(t_token *token);
int					check_if_command(t_token *token, char *envp[]);
int					check_if_export(t_token *token, char **env);
int					check_if_special_char(t_token *token);
int					check_if_path(t_token *token);
int					get_path(char *envp[]);			////gets path////
char				*find_cmd_path(char **paths, char *cmd); ////checks if yo have a path returns null if not////

//////// TOKEN TAB MAKER //////////
void				print_list(t_token *head);				//// prints linked list of t token////
void				free_token_tab(t_token *head);			///free tabs//////
void				close_fds_and_wait_for_childs(t_shell *shell, t_pipe *head);	//// read the function name////
///////////////////////// EXECUTE //////////////////////
void				execute_main(t_shell *shell, t_token *token);				/// redirect you from pipes to no pipes////
void				redirect_exe(t_shell *shell, t_token *token, t_pipe *pipe); /// redirects first intermediates and last commands////
void				apply_pipe_redirection(t_shell *shell, t_pipe *pipe);
void				apply_file_redir_and_go_to_cmd_token(t_token *cmd_token, t_token *temp);
void				skip_to_good_pipe(t_token *cmd_token, t_pipe *pipe);
void				execute_cmd(t_token *token, t_shell *shell, t_pipe *pipe); ////execute the command and free full_p/////
////////////// EXECUTE COMMANDS WHEN NO PIPES /////////////
void				no_pipes(t_token *token, t_shell *shell);
void				cmd_wo_pipes(t_token *token, t_shell *shell);
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
/////////// REDIRECTIONS ////////////////
void				handle_file_redirection(t_token *cmd_token); //// MAIN PART OF REDIRECTIONS /////
void				prepare_redir(t_token *token);
void   				prepare_redir_input(t_token *token);
void				prepare_heredoc(t_token *token, char **env);
int					process_heredoc(t_token *token, char **env);
char 				*search_if_env(char *line, char **env);
char				*generate_random_filename();
int					ft_rand_char(void);
char 				*ft_strcat(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
//////////////////SIGNAUX///////////////

void				ft_signal_handler();
void    			ft_handle_sigint(int sig);
void   				 ft_handle_sigquit(int sig);
void   				ft_setup_heredoc_signals();
void    			ft_restore_signals();
void    			ft_handle_sigsegv();

///// ERRORS///////////////////////////
void				handle_err_execve(t_token *token);
char				*get_prompt_name(t_token *token);

/////////// BUILTIN ////////////

void				identify_builtin(t_token *token, t_shell *shell);
void				builtin_wo_pipes(t_token *token, t_shell *shell);
int					ft_pwd(t_shell *shell);
int 				ft_envp(char **envp);
int 				ft_echo(t_token *tokens, char **env);
char 				*extract_var_name(char *str, int dollar_pos, int str_len);
int					is_n_arg(char *arg);
int					cd_builtin(t_shell *shell, t_token *token, char **env);
int 				ft_setenv(char **envp, char *name, char *value);
int					ft_unset(t_token *tokens, char **env);
int					position_dollar(char *str);
void				ft_exit(t_shell *shell, t_token *tokens);
void   				 update_pwd_vars(char **env);
int					ft_export(t_token *token, char ***env, t_shell *data);
void				handle_export_issue(t_token *token, char ***env, t_shell *data);
void				update_env_var(char ***env, char *var);
char 				*get_home_dir(char **envp);
char				*get_var_name(char *str);
char 				*get_env_value(char *var_name, char **env);
int					is_valid_identifier(char *str);
void				process_echo_string(char *str, char **env, int quote_type);


#endif
