/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:40:30 by ykarakur          #+#    #+#             */
/*   Updated: 2024/08/29 16:40:37 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"
#include <unistd.h>

static int	ft_cd_continued(t_cmd *cmd, char *oldpwd)
{
	if (cmd->flags_array && cmd->flags_array[0][0] == '-')
	{
		if (!oldpwd)
		{
			exit_variable_update(EXIT_SET, 1, 0);
			return (err_print("OLDPWD not set"));
		}
		if (chdir(oldpwd) == -1)
		{
			exit_variable_update(EXIT_SET, 1, 0);
			return (err_print("No such file or directory"));
		}
	}
	else
	{
		if (chdir(cmd->content[0].content) == -1)
		{
			exit_variable_update(EXIT_SET, 1, 0);
			return (err_print("No such file or directory"));
		}
	}
	return (0);
}

int	ft_cd(t_cmd *cmd, t_env *env)
{
	char	*oldpwd;
	char	*pwd;
	char	getcwdbuf[1024];

	oldpwd = env_read("OLDPWD", env);
	pwd = env_read("PWD", env);
	if (counter_content(cmd) + counter_flag(cmd) == 0)
	{
		if (chdir(env_read("HOME", env)) == -1)
			return (exit_variable_update(EXIT_SET, 1, 0),
				err_print("HOME not set"));
	}
	else
	{
		if (ft_cd_continued(cmd, oldpwd) == FAILURE)
			return (exit_variable_update(EXIT_SET, 1, 0), FAILURE);
	}
	if (env_update(env, "OLDPWD", pwd) == 0)
		return (-1);
	if (env_update(env, "PWD", getcwd(getcwdbuf, sizeof(getcwdbuf))) == 0)
		return (-1);
	return (0);
}
