#include "minishell.h"

void	 ft_handle_sigint()
{
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();

}

void	ft_handle_sigsegv()
{
	write(1, "segmentation fault", 19);
	exit (139);
}

void	ft_signal_handler(void)
{
	signal(SIGINT, ft_handle_sigint); ///// CTRL C////
	signal(SIGSEGV, ft_handle_sigsegv); ////SEGFAULT////
	signal(SIGQUIT, SIG_IGN); ///BACKSLASH////
}