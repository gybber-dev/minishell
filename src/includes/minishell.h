#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>

# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include "../../libft/libft.h"

typedef struct	s_all
{
	char     	**command;
	char 		**envs;
	char		specs;
}				t_all;

int				test_fun(int res);


int				is_my_command(char *cmd_name);
void			parser(char *line, t_all *all);


#endif

