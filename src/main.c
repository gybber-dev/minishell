#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Standard readline include files. */
#include <readline/readline.h>
#include <readline/history.h>
#include "includes/minishell.h"

int main(int argc, char** argv)
{
	char *line;


	while (1)
	{
		line = readline("minishell: ");
		if (*line)
			add_history(line);
		// do not free the line!
		parser(line);
		free(line);
	}
	return 0;
}
