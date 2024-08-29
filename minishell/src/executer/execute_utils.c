/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:43:24 by ykarakur          #+#    #+#             */
/*   Updated: 2024/08/29 16:43:26 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"
#include <fcntl.h>

int	is_a_path(char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (command[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	is_paths_define(t_env *env)
{
	if (env_read("PATH", env))
		return (1);
	return (0);
}

void	file_duplicate(t_cmd *cmd)
{
	int	i;

	if (cmd->output_file)
	{
		i = 0;
		while (cmd->output_file[i].name)
		{
			dup2(cmd->output_file[i].fd, 1);
			i++;
		}
	}
	if (cmd->input_file)
	{
		i = 0;
		while (cmd->input_file[i].name)
		{
			dup2(cmd->input_file[i].fd, 0);
			i++;
		}
	}
}

static int	define_output_file(t_cmd *cmd, int *control)
{
	int	i;

	i = 0;
	while (cmd->output_file && cmd->output_file[i].name)
	{
		if (cmd->output_file[i].double_op == 1)
		{
			cmd->output_file[i].fd = open(cmd->output_file[i].name,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		else if (cmd->output_file[i].double_op == 0)
		{
			cmd->output_file[i].fd = open(cmd->output_file[i].name,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		if (cmd->output_file[i].fd == -1)
		{
			err_print("permission denied");
			exit_variable_update(EXIT_SET, 1, 0);
			*control = 1;
			return (FAILURE);
		}
		i++;
	}
	return (0);
}

int	define_input_file(t_cmd *cmd, int *control)
{
	int	i;

	i = 0;
	if (define_output_file(cmd, control) == FAILURE)
		return (1);
	while (cmd->input_file && cmd->input_file[i].name)
	{
		if (cmd->input_file[i].double_op == 0)
		{
			cmd->input_file[i].fd = open(cmd->input_file[i].name,
					O_RDONLY, 0644);
		}
		if (cmd->input_file[i].fd == -1 && cmd->input_file[i].double_op == 0)
		{
			if (access(cmd->input_file[i].name, F_OK) == 0)
				err_print("permission denied");
			else
				err_print("No such file or directory");
			exit_variable_update(EXIT_SET, 1, 0);
			*control = 1;
			return (1);
		}
		i++;
	}
	return (0);
}
