#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>

# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>

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
# define S_AND 7

# define SAFE_TO 1
# define TAKE_FROM 0

typedef struct	s_fd
{
	int			in;
	int			out;
}				t_fd;

typedef struct	s_brack
{
	int		single;
	int 	twice;
}				t_brack;

typedef struct	s_proc
{
	int			is_complex;
	t_fd		fix_fd;
	t_fd		backup_fd;
}				t_proc;

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
	t_proc		proc;
	int			vpid;
	int			vlast;
	int 		is_pipel;
}				t_all;


int 			parser(char **line, t_all *all);
void			lineaddback(char ***src,char *addback);
void			clear_arr_2x(char ***arr);
void			print_array_2x(char **arr);
char			**copy_arrays_2x(char **src_arr);
char			*get_value(char **envs, char *key);
char			*find_binary(char *cmnd, char *paths);
void			init_struct(t_all *all, char **envp);
int				exec_command(t_all *all);
void			std_fd(int opt, t_fd *fd);
int				check_fd(void);
int				processor(char *envp[]);
int				is_builtin(char *command);
int 			ft_echo(char **command, char **env);
int 			ft_export(char **command, char ***env);
int				ft_env(char **command, char **env);
int				ft_cd(char **command, char ***env);
int				ft_unset(char **command, char ***env);
int				ft_exit(char **command);
int				check_flag_n(char *command_1);
char			*get_stdout_fun_result(char **cmd, int (*fun)(char **, char
**), char **env);
char			*get_command_result(char **cmd, char **env);
int				get_arr_2x_len(char **arr);
int				set_value_arr_2x(char *str, char ***arr);
int				check_var_name(char *command);
int 			del_line_arr_2x(char *line, char ***src);
int				ft_pwd(void);
char			*get_pwd(void);
int				ft_error(char *err_msg, int res);
int				ft_perror(char *msg, int res);
int				free_and_return(char **mem, int res);
void			add_tonline(char **n_line, char *prev_head, char **line);
#endif