#include "../includes/minishell.h"


char			*ft_get_one_command(*line)
{
	/**
	 * return one word from line
	 */
	int i;
	char *command;

	i = -1;

	while(line[++i] != ' ')
		;
	command = ft_calloc(i + 1, sizeof(char));
	i = -1;
	while(line[++i] != ' ')
	return command;
}

void			parser(char *line, t_all *all)
{
	/**
	 *1) event = get_one_peace(line, exp)
	 * 2) while (line != '\0' && line != spec)
	 * 			envs[i] = get-one_peace()
	 * 			realloc(envs)
	 * 3) IF LINE == spec
	 * 		specs = line
	 */
	int i;

	i = -1;
	char *tm;
	line = ft_strtrim(line, " ");
//parse bin
// parse args
	while (line[++i])
	{
		*(all->command) = ft_get_one_command(line, &i);
	}

}
