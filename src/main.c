#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Standard readline include files. */
#include <readline/readline.h>
#include <readline/history.h>
#include "includes/minishell.h"

void gel()
{
    ;
}

int main(int argc, char** argv)
{
	char        *line;
    t_all       all;

	while (1)
	{
		line = readline("minishell: ");
		if (*line)
			add_history(line);
		// do not free the line!
		parser(line, &all);
		free(line);
		if (ft_strncmp(line, "exit", 4))
            exit(0);
	}
	return 0;
}
