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


# define PIPE 1
# define LOW 2
# define GT 3
# define LOW2 4
# define GT2 5
# define S_OR 6
# define S_AND 7 //&&

typedef struct s_red
{
	int			type;
	char		*value;
}				t_red;


typedef struct s_cmd
{
	char		**command;
	int			spec;
	t_red		**reds;
}				t_cmd;

/**
** command	(char **)	list of command words
** envs		(char **)	copy of envp (malloced)
** specs	(char)		special symbols:
** vpid		(int)		$$ value
** vlast	(int)		$? value
*/

typedef struct s_all
{
	t_cmd		*cmd;
	char		**envs;
	int			vpid;
	int			vlast;
	int 		is_pipel;
}				t_all;




int				test_fun(int res);

void			clear_arr_2x(char **arr);
void			print_array_2x(char **arr);
char			**copy_arrays_2x(char **src_arr);
char			*get_value(char **envs, char *key);
int				is_my_command(char *cmd_name);
int				parser(char **line, t_all *all);
void			lineaddback(char ***src,char *addback);


void			ft_echo(char *messages);

#endif

