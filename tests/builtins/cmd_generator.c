//
// Created by Ysilla Eschallots on 7/12/21.
//
//extern "C" {
#include "../../src/includes/minishell.h"
#include "builtins.h"
//}

// ls -al | grep o > 111
void		init1(t_all *all, int iter)
{
	all->is_pipel = 0;
	if (iter == 0)
	{
		all->cmd = (t_cmd *) malloc(sizeof(t_cmd));
		all->cmd->command = (char **)malloc(sizeof(char*) * (2 + 1));
		all->cmd->command[0] = ft_strdup("echo");
		all->cmd->command[1] = ft_strdup("hi");;
		all->cmd->command[2] = NULL;

		all->cmd->reds = (t_red **)malloc(sizeof(t_red *) * (1 + 1));
		all->cmd->reds[0] = (t_red *) malloc(sizeof(t_red));
		all->cmd->reds[0]->type = GT;
		all->cmd->reds[0]->value = ft_strdup("_test");
		all->cmd->reds[1] = NULL;

		all->cmd->spec = 0;

		all->vlast = 0;
		all->vpid = 0;
	}
	else if (iter == 1)
		all->cmd = NULL;
}

void		init_all(t_all *all)
{
	all->proc.fix_fd.out = 1;
	all->proc.fix_fd.in = 0;
	std_fd(SAFE_TO, &(all->proc.backup_fd));
	all->envs = NULL;
}


int		generate_cmd(int option, t_all *all, int iter)
{
	if (option == 1)
		init1(all, iter);
}