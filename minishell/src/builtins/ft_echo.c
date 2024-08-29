/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:40:46 by ykarakur          #+#    #+#             */
/*   Updated: 2024/08/29 16:41:13 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"
#include <unistd.h>

static int	is_flag_valid(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	valid_counter_flag(char **flags)
{
	int	i;

	i = 0;
	while (flags && flags[i])
	{
		if (is_flag_valid(flags[i]) == 0)
			break ;
		i++;
	}
	return (i);
}

int	ft_echo(t_cmd *cmd)
{
	int		i;
	int		counter_flag;
	char	**flags;

	flags = cmd->flags_array;
	counter_flag = valid_counter_flag(flags);
	i = counter_flag;
	while (flags && flags[i])
	{
		ft_putstr_fd(flags[i], STDOUT_FILENO);
		if (flags[i + 1] || cmd->content)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	i = 0;
	while (cmd->content && cmd->content[i].content)
	{
		ft_putstr_fd(cmd->content[i].content, STDOUT_FILENO);
		if (cmd->content[i + 1].content)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (counter_flag == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
