#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>



typedef struct	s_all
{
	char     	**command;
	char 		**envs;
	char		specs;
}				t_all;

int				test_fun(int res);

void			parser(char *line);


#endif