#include "minishell.h"

t_global	g_state = {0, 0};

void	ft_handle_sigint(int sig)
{
	(void)sig;
	if (g_state.heredoc_mode)
	{
		write(STDOUT_FILENO, "\n", 1);
		g_state.signal_code = 130;
		exit(130);
	}
	else
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_state.signal_code = 130;
	}
}

void	ft_handle_sigquit(int sig)
{
	(void)sig;
	if (!g_state.heredoc_mode)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_setup_heredoc_signals(void)
{
	g_state.heredoc_mode = 1;
	signal(SIGINT, ft_handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_restore_signals(void)
{
	g_state.heredoc_mode = 0;
	signal(SIGINT, ft_handle_sigint);
	signal(SIGQUIT, ft_handle_sigquit);
}
