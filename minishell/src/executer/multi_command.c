/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:43:50 by ykarakur          #+#    #+#             */
/*   Updated: 2024/08/29 16:43:53 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include <stdlib.h>
#include <sys/wait.h>

static void	wait_all(t_cmd **commands, t_check check)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		if (!commands[i + 1])
			waitpid(commands[i]->p_id, &(check.status), 0);
		else
			waitpid(commands[i]->p_id, 0, 0);
		i++;
	}
	exit_variable_update(EXIT_SET, check.status / 256, 0);
}

static int	multi_restore_files_fd(t_cmd **commands, t_check check, int ori_fd,
	int ori_fd_in)
{
	int	j;

	j = -1;
	while (commands[check.i] && commands[check.i]->output_file
		&& commands[check.i]->output_file[++j].name)
		close(commands[check.i]->output_file[j].fd);
	restore_default_fds(ori_fd, ori_fd_in);
	exit (0);
}

static int	ft_child_process(t_cmd **commands, t_check check,
	int original_fd, int original_fd_in)
{
	close(check.fd[0]);
	if (commands[check.i + 1])
		dup2(check.fd[1], 1);
	close(check.fd[1]);
	if (execute_builtin(commands[check.i], check.env, commands) != INVALID)
		multi_restore_files_fd(commands, check, original_fd, original_fd_in);
	else if (execute_command(commands[check.i], *(check.env)) != 127)
		multi_restore_files_fd(commands, check, original_fd, original_fd_in);
	else
	{
		restore_default_fds(original_fd, original_fd_in);
		err_print_command_not_found(commands[check.i]->command);
		exit(127);
	}
	return (exit_variable_update(EXIT_GET, 0, 0));
}

int	heredoc_exes(t_cmd **commands)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		if (heredoc_exe(commands, i) == FAILURE)
			return (FAILURE);
		i++;
	}
	return (0);
}

int	multi_command_exe(t_cmd **commands, t_env **env,
	int original_fd, int original_fd_in)
{
	t_check	check;

	check = init_check();
	check.env = env;
	check.fd_in = dup(0);
	if (heredoc_last(commands) != -1)
		if (heredoc_exes(commands) == FAILURE)
			return (FAILURE);
	check.i = heredoc_last(commands) + 1;
	while (commands[check.i])
	{
		if (commands[check.i + 1])
			if (pipe(check.fd) == -1)
				return (err_print("pipe error"), FAILURE);
		commands[check.i]->p_id = fork();
		if (commands[check.i]->p_id == 0)
			ft_child_process(commands, check, original_fd, original_fd_in);
		else if (commands[check.i]->p_id < 0)
			return (err_print("fork error"), FAILURE);
		dup2(check.fd[0], 0);
		pipe_close(check);
		check.i++;
	}
	dup2(check.fd_in, 0);
	return (pipe_close(check), wait_all(commands, check), check.status / 256);
}
