#include "../../includes/minishell.h"//void	init_all(t_all *all)//{//	all->command = (char **)malloc(sizeof(char *));//	all->envs = (char **)malloc(sizeof(char *));//	all->specs = ft_calloc(1, sizeof(char));//	(all->command)[0]= NULL;//	(all->command)[1]= NULL;//	(all->envs)[0]= NULL;////}int main(int arc, char **argv, char **envp){	t_all		all;	char 		*line;	all.envs = copy_arrays_2x(envp);	line = ft_strdup(" command1 '> redir1 command2' > redir2");	parser(&line, &all);	printf("from all	reds 1: %s\n", all.cmd->reds[0]->value);	printf("from all reds 2: %s\n", all.cmd->reds[1]->value);	printf("from all command1: %s\n", all.cmd->command[0]);	printf("from all command2: %s\n", all.cmd->command[1]);}