#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>

# include <signal.h>
# include <sys/wait.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/termios.h>
# include "../../libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>

# define PIPE 1
# define LOW 2
# define GT 3
# define LOW2 4
# define GT2 5
# define S_OR 6
# define S_AND 7

# define SAFE_TO 1
# define TAKE_FROM 0
# define HERE_DOC_FILE ".here_doc"
# define BACKUP_FILE ".back"
typedef struct s_fd
{
	int			in;
	int			out;
}				t_fd;

typedef struct s_brack
{
	int		single;
	int		twice;
}				t_brack;

typedef struct s_proc
{
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
	char		*path;
	int			is_builtin;
	int			err;
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
	int			vlast;
	int			is_pipel;
	int			is_finished;
}				t_all;

int				parser(char **line, t_all *all);
void			unc_envs(char **line, t_all *all);
void			lineaddback(char ***src, char *addback);
void			clear_arr_2x(char ***arr);
void			print_array_2x(char **arr);
char			**copy_arrays_2x(char **src_arr);
char			*get_value(char **envs, char *key);
char			*find_binary(char *cmnd, char *paths);
void			exec_command(t_all *all);
void			std_fd(int opt, t_fd *fd);
void			check_fd(void);
int				processor(char *envp[]);
int				is_builtin(char *command);
int				ft_echo(char **command);
int				ft_export(char **command, char ***env);
int				ft_env(char **command, char **env);
int				ft_cd(char **command, char ***env);
int				ft_unset(char **command, char ***env);
void			ft_exit(char **command, int *status);
int				get_arr_2x_len(char **arr);
int				set_value_arr_2x(char *str, char ***arr);
int				check_var_name(char *command);
int				del_line_arr_2x(char *line, char ***src);
int				ft_pwd(void);
char			*get_pwd(void);
int				ft_error(char *err_msg, int res);
int				ft_perror(char *msg, int res);
int				free_and_return(char **mem, int res);
void			add_tonline(char **n_line, char *prev_head, char **line);
int				check_symb(char **line);
int				check_valid(char *line, t_all *all);
int				exec_heredoc(char *breaker, t_all *all);
void			check_quotes(char head, t_brack *br);
int				get_child_status(int status);
int				check_redirs(t_red **reds, t_fd *fix_fd, t_all *all);
void			exec_piple_command(t_all *all);
void			exec_builtin(t_all *all);
void			init_signals(void);
void			init_all(t_all *all, char **envp, int argc, char **argv);
void			print_all(t_all *all);
void			print_and_exit(char *msg, int res);
char			**check_key(char **envs, char *key);
int				init_cmd(t_cmd **cmd);
void			next_head(char **head, char **prev_head);
void			append_back(char *dst, char c);
char			*copy_until_to_end(char stop, char *dst, char *src);
void			check_end(t_cmd *cmd, char **head);
void			quest_func(char **n_line);
void			get_dollar(char **head, char **n_line, t_all *all);
char			*init_unc_envs(t_brack *br, char **head, \
						char **line, char **prev);
void			with_dolr(char **head, char **n_line, char **prev_head);
void			sub_unc_envs(char **prev_head, char **n_line, char **line);
t_cmd			*read_cmd(char **line, t_cmd *cmd);
void			add_cmd(t_cmd *cmd, char **prev_head, char **head);
void			next_cmd(char **head, char **prev_head, \
						char **n_line, t_cmd *cmd);
void			read_redirs(t_cmd *cmd, char **prev_head, char **head);
void			add_tred(t_red ***reds, char *value, int type, t_cmd *cmd);
pid_t			g_status;
#endif
