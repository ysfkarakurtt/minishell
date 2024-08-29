/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:43:46 by ykarakur          #+#    #+#             */
/*   Updated: 2024/08/29 16:43:47 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <sys/wait.h>

static void	requel_heredoc(t_cmd *cmd, int *fd, int i)
{
	char	*str;

	close(fd[0]);
	g_signal = FT_SIGHEREDOC;
	while (1)
	{
		str = readline("> ");
		if (!str)
			break ;
		if (ft_strncmp(str, cmd->input_file[i].name,
				ft_strlen(cmd->input_file[i].name) + 1) == 0)
		{
			free(str);
			break ;
		}
		ft_putendl_fd(str, fd[1]);
		free(str);
	}
	close(fd[1]);
}

int	heredoc(t_cmd *cmd, int i)
{
	int		status;
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		return (err_print("pipe error"), FAILURE);
	pid = fork();
	if (pid == 0)
	{
		if (g_signal == FT_SIGEXIT)
			exit (FT_SIGEXIT);
		requel_heredoc(cmd, fd, i);
		exit(0);
	}
	else if (pid < 0)
		return (err_print("fork error"), FAILURE);
	else
	{
		waitpid(pid, &status, 0);
		g_signal = status / 256;
		close(fd[1]);
		cmd->input_file[0].fd = fd[0];
	}
	return (0);
}
