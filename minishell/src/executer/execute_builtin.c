/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:43:12 by ykarakur          #+#    #+#             */
/*   Updated: 2024/08/29 16:43:13 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

static int	is_builtin(t_cmd *cmd)
{
	return (check_is_builtin(cmd));
}

static int	execute_builtin_continued(t_cmd *cmd, t_env **env, t_cmd **commands)
{
	if (ft_strncmp(cmd->command, "echo", ft_strlen("echo") + 1) == 0)
		return (ft_echo(cmd));
	else if (ft_strncmp(cmd->command, "cd", ft_strlen("cd") + 1) == 0)
		return (ft_cd(cmd, *env));
	else if (ft_strncmp(cmd->command, "pwd", ft_strlen("pwd") + 1) == 0)
		return (ft_pwd());
	else if (ft_strncmp(cmd->command, "export", ft_strlen("export") + 1) == 0)
		return (ft_export(cmd, env));
	else if (ft_strncmp(cmd->command, "unset", ft_strlen("unset") + 1) == 0)
		return (ft_unset(cmd, env));
	else if (ft_strncmp(cmd->command, "env", ft_strlen("env") + 1) == 0)
		return (ft_env(*env));
	else if (ft_strncmp(cmd->command, "exit", ft_strlen("exit") + 1) == 0)
		return (ft_exit(cmd, env, commands));
	return (INVALID);
}

int	execute_builtin(t_cmd *cmd, t_env **env, t_cmd **commands)
{
	int	check;

	check = 0;
	if (!cmd->command)
		return (INVALID);
	if (!is_builtin(cmd))
		return (INVALID);
	if (define_input_file(cmd, &check) == FAILURE)
		return (FAILURE);
	if (check == 1)
		return (FAILURE);
	file_duplicate(cmd);
	return (execute_builtin_continued(cmd, env, commands));
}

void	pipe_close(t_check	check)
{
	close(check.fd[0]);
	close(check.fd[1]);
}

int	check_is_builtin(t_cmd *cmd)
{
	if (ft_strncmp(cmd->command, "echo", ft_strlen("echo") + 1) == 0)
		return (1);
	else if (ft_strncmp(cmd->command, "cd", ft_strlen("cd") + 1) == 0)
		return (1);
	else if (ft_strncmp(cmd->command, "pwd", ft_strlen("pwd") + 1) == 0)
		return (1);
	else if (ft_strncmp(cmd->command, "export", ft_strlen("export") + 1) == 0)
		return (1);
	else if (ft_strncmp(cmd->command, "unset", ft_strlen("unset") + 1) == 0)
		return (1);
	else if (ft_strncmp(cmd->command, "env", ft_strlen("env") + 1) == 0)
		return (1);
	else if (ft_strncmp(cmd->command, "exit", ft_strlen("exit") + 1) == 0)
		return (1);
	return (0);
}
