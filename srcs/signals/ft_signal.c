#include "minishell.h"

void	ft_handle_sigsegv(int sig)
{
	(void)sig;
	write(1, "segmentation fault", 19);
	exit(139);
}

void	ft_signal_handler(void)
{
	signal(SIGSEGV, ft_handle_sigsegv);
	signal(SIGINT, ft_handle_sigint);
	signal(SIGQUIT, ft_handle_sigquit);
}
