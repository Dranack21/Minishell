#include "minishell.h"

static int	handle_home_path(char **env, char **path)
{
	*path = get_home_dir(env);
	if (!*path)
	{
		printf("cd: HOME not set\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	handle_oldpwd(char **path)
{
	*path = getenv("OLDPWD");
	if (!*path)
	{
		printf("cd: OLDPWD not set\n");
		return (EXIT_FAILURE);
	}
	printf("%s\n", *path);
	return (EXIT_SUCCESS);
}

static int	get_cd_path(t_token *token, char **env, char **path)
{
	t_token	*arg;

	arg = token->next;
	if (!arg || (ft_strcmp(arg->str, "~") == 0))
		return (handle_home_path(env, path));
	else if (ft_strcmp(arg->str, "-") == 0)
		return (handle_oldpwd(path));
	*path = arg->str;
	return (EXIT_SUCCESS);
}

int	cd_builtin(t_shell *shell, t_token *token, char **env)
{
	char	*path;
	t_token	*temp;

	if (token)
	{
		temp = NULL;
		if (token->next)
			temp = token->next;
		if (temp && temp->next && temp->next->type == ARG)
		{
			printf("cd : too many arguments ^^\n");
			return (shell->exit_code = 1, EXIT_FAILURE);
		}
	}
	if (get_cd_path(token, env, &path) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (chdir(path) != 0)
	{
		perror("cd");
		shell->exit_code = 1;
		return (EXIT_FAILURE);
	}
	update_pwd_vars(env);
	return (shell->exit_code = 0, EXIT_SUCCESS);
}
