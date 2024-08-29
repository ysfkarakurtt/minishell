/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:41:51 by ykarakur          #+#    #+#             */
/*   Updated: 2024/08/29 16:42:02 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"
#include <unistd.h>

static int	total_cmd_counter(t_cmd *cmd, t_cmd **commands, int flag)
{
	int	total_command_count;
	int	i;

	i = -1;
	total_command_count = 0;
	if (flag == 0)
	{
		while (cmd->flags_array && cmd->flags_array[++i])
			total_command_count++;
		i = -1;
		while (cmd->content && cmd->content[++i].content)
			total_command_count++;
		return (total_command_count);
	}
	else
	{
		while (commands[++i])
			total_command_count++;
		return (total_command_count);
	}
}

static void	ft_exit_error(t_cmd *cmd, int flag)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	if (!flag)
		ft_putstr_fd(cmd->content[0].content, 2);
	else
		ft_putstr_fd(cmd->flags_array[0], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(255);
}

static void	ft_exit_by_exit_value(t_cmd *cmd, t_env **envp, t_cmd **commands)
{
	int	return_value;
	int	flag;

	flag = 1;
	return_value = ft_atoi(cmd->flags_array[0], &flag);
	if (flag == 0)
		ft_exit_error(cmd, 1);
	ft_putstr_fd("exit\n", 1);
	free_env(*envp);
	free(envp);
	free_commands(commands);
	exit((256 + return_value) % 256);
}

static void	ft_content_exit(t_cmd *cmd, t_env **envp, t_cmd **commands)
{
	int	return_value;
	int	flag;

	flag = 1;
	return_value = ft_atoi(cmd->content[0].content, &flag);
	if (flag == 0)
		ft_exit_error(cmd, 0);
	ft_putstr_fd("exit\n", 1);
	free_env(*envp);
	free(envp);
	free_commands(commands);
	exit((256 + return_value) % 256);
}

int	ft_exit(t_cmd *cmd, t_env **envp, t_cmd **commands)
{
	int	command_count;
	int	command_count2;

	command_count = total_cmd_counter(cmd, commands, 0);
	command_count2 = total_cmd_counter(cmd, commands, 1);
	if (command_count == 0)
	{
		if (command_count2 == 1)
			ft_putstr_fd("exit\n", 1);
		free_env(*envp);
		free(envp);
		free_commands(commands);
		exit(exit_variable_update(EXIT_GET, 0, 0));
	}
	if (command_count > 1)
	{
		ft_content_exit(cmd, envp, commands);
		return (1);
	}
	if (cmd->flags_array && cmd->flags_array[0])
		ft_exit_by_exit_value(cmd, envp, commands);
	if (cmd->content && cmd->content[0].content)
		ft_content_exit(cmd, envp, commands);
	return (0);
}
