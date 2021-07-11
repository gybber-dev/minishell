#include "../includes/minishell.h"

int			execute(char **cmd, char *paths)
{
	char	*path;

	path = find_binary(cmd[0], paths);

	return 0;
}

void		clear(t_all *all)
{
	;
}

int			builtins(t_all *all)
{
	// TODO Gybber
	return 0;
}

void		my_init_all(t_all *all, char **envp, int iter)
{
	if (iter == 0)
	{
		all->cmd = (t_cmd *) malloc(sizeof(t_cmd));
		all->cmd->command = (char **)malloc(sizeof(char*) * (1 + 1));
		all->cmd->command[0] = ft_strdup("ls");
		all->cmd->command[1] = NULL;

		all->cmd->reds = (t_red **)malloc(sizeof(t_red *) * (1 + 1));
		all->cmd->reds[0] = (t_red *) malloc(sizeof(t_red));
		all->cmd->reds[0]->type = GT;
		all->cmd->reds[0]->value = "1";
		all->cmd->reds[1] = NULL;
		all->cmd->spec = 0;

		all->vlast = 0;
		all->vpid = 0;
		all->envs = copy_arrays_2x(envp);
		print_array_2x(all->envs);
	}
	else if (iter == 1)
	{
		all->cmd = NULL;
	}
}

//int main(int argc, char *argv[], char *envp[])
//{
//	t_all all;
//	int		i;
//
//	i = 0;
//	while (1)
//	{
//		my_init_all(&all, envp, i);
//		if (!all.cmd)
//			break;
//		builtins(&all);
//		clear(&all);
//		i++;
//	}
//////	char *arr[3] = {"ar=2", "b=3", NULL};
//////	char *res = get_value(arr, "ar");
////	char *val = get_value(all.envs, "PATH=");
//	return 0;
//}
