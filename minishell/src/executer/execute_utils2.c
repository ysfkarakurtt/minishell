/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:43:31 by ykarakur          #+#    #+#             */
/*   Updated: 2024/08/29 16:43:33 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	restore_default_fds(int original_fd, int original_fd_in)
{
	dup2(original_fd, 1);
	dup2(original_fd_in, 0);
	close(original_fd);
	close(original_fd_in);
}
