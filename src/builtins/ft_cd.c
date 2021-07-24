#include "../includes/minishell.h"

static int	exec_cd(char *path, char ***env)
{
	char		*old_path;
	char		*new_path;
	char		*tmp;

	old_path = get_pwd();
	if (!old_path)
		return (1);
	if (chdir(path) == -1)
		return (free_and_return(&old_path, 1) * ft_perror("cd", 1));
	new_path = get_pwd();
	if (!new_path)
		return (free_and_return(&old_path, 1));
	tmp = ft_strjoin("PWD=", new_path);
	if (tmp == NULL)
		return (free_and_return(&old_path, 1) * free_and_return(&new_path, 1));
	if (set_value_arr_2x(tmp, env) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	free(tmp);
	tmp = ft_strjoin("OLDPWD=", old_path);
	if (!tmp)
		return (free_and_return(&old_path, 1) * free_and_return(&new_path, 1));
	if (set_value_arr_2x(tmp, env) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	free(tmp);
	return (free_and_return(&old_path, 0) * free_and_return(&new_path, 0));
}

static int	exec_with_home(char **command, char *home, char ***env)
{
	char		*tmp;

	tmp = command[1];
	tmp = ft_strjoin(home, (tmp + 1));
	if (!tmp)
		return (EXIT_FAILURE);
	free(command[1]);
	command[1] = tmp;
	return (exec_cd(command[1], env));
}

int	ft_cd(char **command, char ***env)
{
	int			len;
	char		*home;

	home = NULL;
	len = get_arr_2x_len(command);
	if (len > 2)
		return (ft_error("cd: too many arguments", EXIT_FAILURE));
	if (len == 1 || *(command[1]) == '~')
	{
		home = get_value(*env, "HOME");
		if (!home)
			return (ft_error("cd: HOME not set", EXIT_FAILURE));
	}
	if (len == 1)
		return (exec_cd(home, env));
	if (len == 2 && !home)
		return (exec_cd(command[1], env));
	if (len == 2 && home != NULL)
		return (exec_with_home(command, home, env));
	return (EXIT_SUCCESS);
}
