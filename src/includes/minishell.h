#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>

# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>

//#include "/Users/yeschall/.brew/opt/readline/include/readline/readline.h"
//#include "/Users/yeschall/.brew/opt/readline/include/readline/history.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/termios.h>


# include "../../libft/libft.h"
#include <sys/stat.h>

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

typedef struct s_proc
{
	int			is_complex;
}				t_proc;


typedef struct s_all
{
	char		**command;
	char		**envs;
	char		specs;
	int			vpid;
	int			vlast;
	t_proc		proc;
}				t_all;

# define PIPE 1
# define LOW 2
# define GT 3
# define LOW2 4
# define GT2 5
# define S_OR 6
# define S_AND 7


int				test_fun(int res);

void			clear_arr_2x(char **arr);
void			print_array_2x(char **arr);
char			**copy_arrays_2x(char **src_arr);
char			*get_value(char **envs, char *key);
int				is_my_command(char *cmd_name);
int				parser(char *line, t_all *all);
char			*find_binary(char *cmnd, char *paths);

void			ft_echo(char *messages);

#endif

