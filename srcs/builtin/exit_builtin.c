/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:04:48 by habouda           #+#    #+#             */
/*   Updated: 2025/02/12 23:53:58 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

int	ft_exit(t_shell *shell, t_token *tokens)
{
	t_token	*arg;
	int		exit_code;
	int		temp;

	printf("exit\n");
	arg = tokens->next;
	if (!arg)
		return (0);
	if (!is_numeric(arg->str))
	{
		write(2, "exit: ", 7);
		write(2, arg->str, ft_strlen(arg->str));
		write(2, ": numeric argument required\n", 29);
		return (2);
	}
	exit_code = atoi(arg->str);
	temp = exit_code % 256;
	if (arg->next)
	{
		write(2, "exit: too many arguments\n", 26);
		shell->exit_code = 2;
		return (2);
	}
	return (temp);
}
