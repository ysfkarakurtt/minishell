/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_execv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:43:18 by ykarakur          #+#    #+#             */
/*   Updated: 2024/08/29 16:43:20 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include <stdlib.h>
#include <sys/wait.h>

int	is_heredoc(t_cmd *cmd)
{
	int	j;

	j = -1;
	if (cmd->input_file)
	{
		while (cmd->input_file[++j].name)
		{
			if (cmd->input_file[j].double_op == 1)
				return (1);
		}
	}
	return (0);
}

static int	execute_fork(t_cmd *cmd, t_check check, t_env *env)
{
	if (!cmd->command && !is_heredoc(cmd))
		exit (1);
	if (!cmd->command && is_heredoc(cmd))
		exit(exit_variable_update(EXIT_GET, 0, 0));
	if (access(cmd->command, F_OK) == 0 && access(cmd->command, X_OK) == 0)
	{
		if (execve(cmd->command, check.args_arr, 0) != 0)
			exit(127);
	}
	else if (!is_paths_define(env))
		exit(127);
	else if (execve(check.path, check.args_arr, check.env_arr) != 0)
		exit(127);
	exit(0);
}

static void	free_execute_args(char **args, char *path, char **env_arr)
{
	free_double_char(args);
	free(path);
	free_double_char(env_arr);
}

static int	execute_command_continued(t_cmd *cmd, t_env *env, t_check check)
{
	check.pid = fork();
	if (check.pid < 0)
	{
		free_execute_args(check.args_arr, check.path, check.env_arr);
		return (err_print("fork error"), FAILURE);
	}
	if (check.pid == 0)
	{
		file_duplicate(cmd);
		execute_fork(cmd, check, env);
	}
	if (check.pid > 0 && (check.fd[0] != -1 && check.fd[1] != -1))
	{
		close(check.fd[0]);
		close(check.fd[1]);
	}
	waitpid(check.pid, &check.status, 0);
	exit_variable_update(EXIT_SET, check.status / 256, 0);
	return (free_execute_args(check.args_arr, check.path, check.env_arr),
		check.status / 256);
}

int	execute_command(t_cmd *cmd, t_env *env)
{
	int		control;
	t_check	check;

	control = 0;
	check.path = get_command_path(cmd->command, env);
	check.fd[0] = -1;
	check.fd[1] = -1;
	if (!check.path)
		return (err_print(MALLOC_ERR), 0);
	check.args_arr = set_arg_array(cmd);
	if (!check.args_arr)
		return (free(check.path), err_print(MALLOC_ERR), 0);
	check.env_arr = set_env_array(env);
	if (!check.env_arr)
		return (free_double_char(check.args_arr),
			free(check.path), err_print(MALLOC_ERR), 0);
	if (define_input_file(cmd, &control) == 1)
		return (free_execute_args(check.args_arr, check.path, check.env_arr),
			1);
	return (execute_command_continued(cmd, env, check));
}
