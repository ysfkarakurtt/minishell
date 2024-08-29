/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:45:28 by ykarakur          #+#    #+#             */
/*   Updated: 2024/08/29 16:45:30 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include "../../libft/libft.h"

int	err_print_command_not_found(char *command)
{
	ft_putstr_fd("\033[31m", 2);
	ft_putstr_fd("minishell", 2);
	ft_putstr_fd("\033[0m: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (FAILURE);
}

int	err_print(char *error_type)
{
	ft_putstr_fd("\033[31m", 2);
	ft_putstr_fd("minishell", 2);
	ft_putstr_fd("\033[0m: ", 2);
	ft_putstr_fd(error_type, 2);
	ft_putstr_fd("\n", 2);
	return (FAILURE);
}
