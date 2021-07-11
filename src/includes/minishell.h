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
#include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

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

typedef struct s_cmd
{
	char		**command;
	int			spec;
}				t_cmd;


typedef struct s_all
{
	t_cmd		*cmd;
	char		**envs;
	int			vpid;
	int			vlast;
}				t_all;


# define PIPE 1
# define LOW 2
# define GT 3
# define LOW2 4
# define GT2 5
# define S_OR 6
# define S_AND 7

int hello();
int				test_fun(int res);

void			clear_arr_2x(char **arr);
void			print_array_2x(char **arr);
char			**copy_arrays_2x(char **src_arr);
char			*get_value(char **envs, char *key);
int				is_my_command(char *cmd_name);
int				parser(char *line, t_all *all);
int				check_valid(char *line);


void			ft_echo(char *messages);

#endif

