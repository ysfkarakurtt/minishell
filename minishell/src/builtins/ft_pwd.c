/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:42:24 by ykarakur          #+#    #+#             */
/*   Updated: 2024/08/29 16:42:26 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	ft_pwd(void)
{
	char	pwd[1024];

	getcwd(pwd, sizeof(pwd));
	printf("%s\n", pwd);
	return (0);
}
