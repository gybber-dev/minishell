#include "../includes/minishell.h"

int	is_shell(char *command)
{
	if (!command || *command == '\0')
		return (0);
	if (ft_strnstr(command, "minishell", ft_strlen(command) + 1))
		return (1);
	return (0);
}

int	is_builtin(char *command)
{
	if (!command)
		return (0);
	return (!(ft_strncmp(command, "echo", (ft_strlen(command) + 1)) && \
			ft_strncmp(command, "cd", (ft_strlen(command) + 1)) && \
			ft_strncmp(command, "export", (ft_strlen(command) + 1)) && \
			ft_strncmp(command, "unset", (ft_strlen(command) + 1)) && \
			ft_strncmp(command, "exit", (ft_strlen(command) + 1)) && \
			ft_strncmp(command, "env", (ft_strlen(command) + 1)) && \
			ft_strncmp(command, "pwd", (ft_strlen(command) + 1))));
}

void	exec_builtin(t_all *all)
{
	if (!ft_strncmp(all->cmd->command[0], "echo", 5))
		all->vlast = ft_echo(all->cmd->command);
	else if (!ft_strncmp(all->cmd->command[0], "pwd", 4))
		all->vlast = ft_pwd();
	else if (!ft_strncmp(all->cmd->command[0], "export", 7))
		all->vlast = ft_export(all->cmd->command, &(all->envs));
	else if (!ft_strncmp(all->cmd->command[0], "unset", 6))
		all->vlast = ft_unset(all->cmd->command, &(all->envs));
	else if (!ft_strncmp(all->cmd->command[0], "cd", 3))
		all->vlast = ft_cd(all->cmd->command, &(all->envs));
	else if (!ft_strncmp(all->cmd->command[0], "env", 4))
		all->vlast = ft_env(all->cmd->command, all->envs);
	else if (!ft_strncmp(all->cmd->command[0], "exit", 5))
		ft_exit(all->cmd->command, &(all->vlast));
}
