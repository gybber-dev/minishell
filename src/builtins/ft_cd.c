#include "../includes/minishell.h"

static int		exec_cd(char *path, char ***env)
{
	char		*old_path;
	char		*new_path;
	char		*tmp;

	return 0;
//	old_path = get_pwd();
//	if (!old_path)
//		return 0;
//	if (chdir(path) == -1)
//	{
//		free(old_path);
//		return 0;
//	}
//	if (!(new_path = get_pwd()))
//	{
//		free(old_path);
//		return 0;
//	}
//	if (!(tmp = ft_strjoin("PWD=", new_path)))
//	{
//		free(old_path);
//		free(new_path);
//		return 0;
//	}
//	ft_export(tmp);  // TODO
//	free(tmp);
//	if (!(tmp = ft_strjoin("OLDPWD=", old_path)))
//	{
//		free(old_path);
//		free(new_path);
//		return 0;
//	}
//	ft_export(tmp); // TODO
//	free(tmp);
//	free(old_path);
//	free(new_path);
//	ft_free({old_path, new_path}, 2);

	return 1;
}


int				ft_cd(char **command, char ***env)
{
	int			len;
	char		*home;

	home = NULL;
	if ((len = get_arr_2x_len(command)) > 2)
		exit(EXIT_FAILURE);
	if (len == 1 || *(command[1]) == '~')
		if (!(home = get_value(*env, "HOME")))
			exit(EXIT_FAILURE); // Home not set
	if (len == 1 || (len == 2 && !home)



}