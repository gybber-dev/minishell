#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>


typedef struct	s_parser
{
	char		*command;
	char		**args;
}				t_parser;

typedef struct	s_all
{
	t_parser 	*command;
	char 		**ENV;
	int			FLAGS;
}				t_all;

int				test_fun(int res);

void			parser(char *line);


#endif