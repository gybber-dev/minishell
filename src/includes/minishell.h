#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>

# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>

/**
** command	(char **)	list of command words
** envs		(char **)	copy of envp (malloced)
** specs	(char)		special symbols:
**		'0'				no specs
**		'|'				pipes
**		'<'				redir1
**		'>'				redir2
**		'3'				redir3 >>
**		'4'				redir4 <<
**		'5'				||
**		'6'				&&
** vpid		(int)		$$ value
** vlast	(int)		$? value
*/

typedef struct s_all
{
	char		**command;
	char		**envs;
	char		specs;
	int			vpid;
	int			vlast;
}				t_all;

int				test_fun(int res);

void			parser(char *line, t_all *all);

#endif