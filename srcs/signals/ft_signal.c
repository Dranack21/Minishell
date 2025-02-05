#include "minishell.h"

static int	g_in_heredoc = 0;

void	ft_handle_sigint(int sig)
{
	(void)sig;
	if (g_in_heredoc)
	{
		write(STDOUT_FILENO, "\n", 1);
		exit(130);
	}
	else
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_handle_sigquit(int sig)
{
	(void)sig;
	if (!g_in_heredoc)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_handle_sigsegv()
{
	write(1, "segmentation fault", 19);
	exit(139);
}

void	ft_setup_heredoc_signals()
{
	g_in_heredoc = 1;
	signal(SIGINT, ft_handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_restore_signals()
{
	g_in_heredoc = 0;
	signal(SIGINT, ft_handle_sigint);
	signal(SIGQUIT, ft_handle_sigquit);
}

void	ft_signal_handler()
{
	signal(SIGSEGV, ft_handle_sigsegv);
	signal(SIGINT, ft_handle_sigint);
	signal(SIGQUIT, ft_handle_sigquit);
}