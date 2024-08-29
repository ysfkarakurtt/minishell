/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:43:40 by ykarakur          #+#    #+#             */
/*   Updated: 2024/08/29 16:43:41 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

int	heredoc_exe(t_cmd **commands, int i)
{
	int	j;

	j = -1;
	if (commands[i]->input_file)
	{
		while (commands[i]->input_file[++j].name)
		{
			if (commands[i]->input_file[j].double_op == 1)
			{
				if (heredoc(commands[i], j) == FAILURE)
				{
					exit_variable_update(EXIT_SET, 1, 0);
					return (FAILURE);
				}
			}
		}
	}
	if (g_signal == FT_SIGEXIT)
	{
		exit_variable_update(EXIT_SET, 1, 0);
		return (FAILURE);
	}
	return (0);
}

static int	restore_files_fd(t_cmd **commands, int fd_orig_1, int fd_orig_0)
{
	int	i;

	i = 0;
	while (commands[0] && commands[0]->output_file
		&& commands[0]->output_file[i].name)
	{
		close(commands[0]->output_file[i].fd);
		i++;
	}
	i = 0;
	while (commands[0] && commands[0]->input_file
		&& commands[0]->input_file[i].name)
	{
		close(commands[0]->input_file[i].fd);
		i++;
	}
	restore_default_fds(fd_orig_1, fd_orig_0);
	return (0);
}

static int	execute_single_command(t_cmd **commands, t_env **env)
{
	int	fd_orig_1;
	int	fd_orig_0;

	fd_orig_0 = dup(0);
	fd_orig_1 = dup(1);
	if (heredoc_exe(commands, 0) == FAILURE)
		return (FAILURE);
	if (execute_builtin(commands[0], env, commands) != INVALID)
		return (restore_files_fd(commands, fd_orig_1, fd_orig_0));
	else if (execute_command(commands[0], *env) != 127)
	{
		restore_default_fds(fd_orig_1, fd_orig_0);
		return (0);
	}
	else
	{
		restore_default_fds(fd_orig_1, fd_orig_0);
		exit_variable_update(EXIT_SET, 127, 0);
		err_print_command_not_found(commands[0]->command);
		return (FAILURE);
	}
	return (0);
}

int	heredoc_last(t_cmd **commands)
{
	int	tmp;
	int	j;
	int	i;

	j = -1;
	i = -1;
	tmp = -1;
	while (commands[++i])
	{
		if (commands[i]->input_file)
		{
			while (commands[i]->input_file[++j].name)
			{
				if (commands[i]->input_file[j].double_op == 1)
					tmp = i;
			}
		}
	}
	return (tmp);
}

int	execute_commands(t_cmd **commands, t_env **env)
{
	int	fd_orig_0;
	int	fd_orig_1;

	g_signal = FT_SIGST;
	if (commands[0]->command
		&& ft_strncmp(commands[0]->command, "exit", ft_strlen("exit") + 1) != 0)
		exit_variable_update(EXIT_SET, 0, 0);
	if (!commands)
		return (0);
	fd_orig_1 = dup(1);
	fd_orig_0 = dup(0);
	if (counter_command(commands) == 1)
	{
		if (execute_single_command(commands, env) == FAILURE)
			return (FAILURE);
	}
	else
		return (multi_command_exe(commands, env, fd_orig_1, fd_orig_0));
	return (0);
}
