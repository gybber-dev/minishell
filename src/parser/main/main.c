#include "../../includes/minishell.h"//void	init_all(t_all *all)//{//	all->command = (char **)malloc(sizeof(char *));//	all->envs = (char **)malloc(sizeof(char *));//	all->specs = ft_calloc(1, sizeof(char));//	(all->command)[0]= NULL;//	(all->command)[1]= NULL;//	(all->envs)[0]= NULL;////}int main(int arc, char **argv, char **envp){	t_all		all;	char 		*line;	all.envs = copy_arrays_2x(envp);	line = ft_strdup("  haha $PWD");//	char **tmp;////	tmp = (char **)malloc(sizeof(char *) * 5);//	tmp[0] = ft_strdup("my");//	tmp[1] = ft_strdup("Name");//	tmp[2] = ft_strdup("is");//	tmp[3] = ft_strdup("Deckard");//	tmp[4] = NULL;////	lineaddback(&tmp, "Sausag");//	while(*tmp != NULL)//	printf("%s\n", *tmp++);	parser(&line, &all);//	init_all(&all);//	printf("%d\n", check_valid(" > 2"));//	parser("  'line  hah'", &all);//	printf("%s\n", *(all.command));//	printf("strncmp: %d\n", ft_strncmp("> ddd", ">", 1));//	parser("hah", &all);}