#include "../includes/minishell.h"

void	quest_func(char **n_line, t_all *all)
{
	char	*prev_head;
	char	*tmp;

	prev_head = *n_line;
	tmp = ft_itoa(all->vlast);
	*n_line = ft_strjoin(prev_head, tmp);
	if (!(*n_line))
		*n_line = ft_strdup(tmp);
	free_and_return(&tmp, 1);
	free_and_return(&prev_head, 1);
}

void	get_dollar(char **head, char **n_line, t_all *all)
{
	char	*prev_head;
	char	*tmp;

	if (**head == '?' && (*head)++)
		quest_func(n_line, all);
	else if (ft_isdigit(**head))
		(*head)++;
	else if (ft_isalpha(**head) || **head == '_')
	{
		prev_head = *head;
		while (ft_isdigit(**head) || ft_isalpha(**head) || **head == '_')
			(*head)++;
		tmp = ft_substr(prev_head, 0, *head - prev_head);
		prev_head = tmp;
		tmp = get_value(all->envs, prev_head);
		if (tmp)
		{
			free_and_return(&prev_head, 1);
			prev_head = *n_line;
			*n_line = ft_strjoin(prev_head, tmp);
			if (!(*n_line))
				*n_line = ft_strdup(tmp);
			free_and_return(&prev_head, 1);
		}
	}
}

char	*init_unc_envs(t_brack *br, char **head, char **line, char **prev)
{
	*br = (t_brack){0, 0};
	*head = *line;
	*prev = *head;
	return (NULL);
}

void	with_dolr(char **head, char **n_line, char **prev_head)
{
	char	*tmp;

	*(*head)++ = '$';
	tmp = *n_line;
	*prev_head = ft_substr(*prev_head, 0, *head - *prev_head);
	*n_line = ft_strjoin(tmp, *prev_head);
	if (!(*n_line))
	{
		*n_line = *prev_head;
		free_and_return(&tmp, 0);
	}
	else
		free_and_return(prev_head, 1);
}

void	sub_unc_envs(char **prev_head, char **n_line, char **line)
{
	if (ft_strlen(*prev_head))
		add_tonline(n_line, *prev_head, line);
	if (*n_line && free_and_return(line, 1))
		*line = *n_line;
}
