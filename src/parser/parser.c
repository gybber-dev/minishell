#include "../includes/minishell.h"

void	check_quotes(char head, t_brack *br)
{
	if (head == '\'')
	{
		if (br->single)
			br->single = 0;
		else
			br->single = 1;
	}
	if (head == '\"')
	{
		if (br->twice)
			br->twice = 0;
		else
			br->twice = 1;
	}
}

void	add_tonline(char **n_line, char *prev_head, char **line)
{
	char	*tmp;

	tmp = *n_line;
	if (ft_strlen(prev_head))
	{
		*n_line = ft_strjoin(tmp, prev_head);
		if (!(*n_line))
			*n_line = ft_strdup(*line);
		free_and_return(&tmp, 0);
	}
}

void	unc_envs(char **line, t_all *all)
{
	char	*head;
	char	*prev_head;
	char	*n_line;
	t_brack	br;

	n_line = init_unc_envs(&br, &head, line, &prev_head);
	while (*head != '\0')
	{
		check_quotes(*head, &br);
		if (*head == '$' && !br.single)
		{
			*head++ = '\0';
			if (*head == '\'' && br.twice && head--)
				with_dolr(&head, &n_line, &prev_head);
			else
				add_tonline(&n_line, prev_head, line);
			get_dollar(&head, &n_line, all);
			prev_head = head;
		}
		else
			head++;
	}
	sub_unc_envs(&prev_head, &n_line, line);
}

int	parser(char **line, t_all *all)
{
	char	*head;
	t_cmd	*cmd;

	if (init_cmd(&cmd))
		return (-1);
	head = *line;
	*line = ft_strtrim((const char *)(head), " ");
	free(head);
	unc_envs(line, all);
	all->cmd = read_cmd(line, cmd);
	if (all->cmd->spec)
		all->is_pipel = 1;
	if (all->cmd->err)
		return (-1);
	return (all->cmd->spec);
}
