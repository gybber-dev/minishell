#include "../includes/minishell.h"

static int		exec_cd(char *path, char ***env)
{
	char		*old_path;
	char		*new_path;
	char		*tmp;

	old_path = get_pwd();
	if (!old_path)
		return 0;
	if (chdir(path) == -1)
		return free_and_return(&old_path, 0);
	new_path = get_pwd();
	if (!new_path)
		return free_and_return(&old_path, 0);
	if (!(tmp = ft_strjoin("PWD=", new_path)))
		return (free_and_return(&old_path, 0) * free_and_return(new_path, 0));
	set_value_arr_2x(tmp, env);
	free(tmp);
	if (!(tmp = ft_strjoin("OLDPWD=", old_path)))
		return (free_and_return(&old_path, 0) * free_and_return(new_path, 0));
	set_value_arr_2x(tmp, env);
	free(tmp);
	free_and_return(&old_path, 1);
	free_and_return(&new_path, 1);
}


int				ft_cd(char **command, char ***env)
{
	int			len;
	char		*home;
	char		*tmp;

	home = NULL;
	if ((len = get_arr_2x_len(command)) > 2)
		exit(EXIT_FAILURE);
	if (len == 1 || *(command[1]) == '~')
		if (!(home = get_value(*env, "HOME")))
			exit(EXIT_FAILURE); // Home not set
	if (len == 1)
		return exec_cd(home, env);
	if (len == 2 && !home)
		return exec_cd(command[1], env);
	if (len == 2 && home)
	{
		tmp = command[1];
		if (!(tmp = ft_strjoin(home, (command[1] + 1))))
			return 0;
		free(command[1]);
		command[1] = tmp;
		return exec_cd(command[1], env);
	}
	return 1;
}