#include "../includes/minishell.h"

static int		exec_cd(char *path, char ***env)
{
	char		*old_path;
	char		*new_path;
	char		*tmp;

	old_path = get_pwd();
	if (!old_path)
		return 1;
	if (chdir(path) == -1)
		return free_and_return(&old_path, 1);
	new_path = get_pwd();
	if (!new_path)
		return free_and_return(&old_path, 1);
	if (!(tmp = ft_strjoin("PWD=", new_path)))
		return (free_and_return(&old_path, 1) * free_and_return(&new_path, 1));
	if (set_value_arr_2x(tmp, env))
		return (EXIT_FAILURE);
	free(tmp);
	if (!(tmp = ft_strjoin("OLDPWD=", old_path)))
		return (free_and_return(&old_path, 1) * free_and_return(&new_path, 1));
	if (set_value_arr_2x(tmp, env))
		return (EXIT_FAILURE);
	free(tmp);
	free_and_return(&old_path, 0);
	free_and_return(&new_path, 0);
	return (EXIT_SUCCESS);
}


int				ft_cd(char **command, char ***env)
{
	int			len;
	char		*home;
	char		*tmp;

	home = NULL;
	if ((len = get_arr_2x_len(command)) > 2)
		return 1;
	if (len == 1 || *(command[1]) == '~')
		if (!(home = get_value(*env, "HOME")))
			return 1;
	if (len == 1)
		return exec_cd(home, env);
	if (len == 2 && !home)
		return exec_cd(command[1], env);
	if (len == 2 && home)
	{
		tmp = command[1];
		if (!(tmp = ft_strjoin(home, (command[1] + 1))))
			return 1;
		free(command[1]);
		command[1] = tmp;
		return exec_cd(command[1], env);
	}
	return 0;
}