#include "../../includes/minishell.h"

t_all       all;
void	init_all(t_all *all)
{
	all->command = (char **)malloc(sizeof(char *));
	all->envs = (char **)malloc(sizeof(char *));
	all->specs = ft_calloc(1, sizeof(char));
	(all->command)[0]= NULL;
	(all->envs)[0]= NULL;

}
int main(int arc, char **argv)
{
	t_all       all;

	init_all(&all);
	printf("%s\n", all.command);
//	parser(" 123 /", &all);
}