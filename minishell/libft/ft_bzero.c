/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:34:21 by ykarakur          #+#    #+#             */
/*   Updated: 2024/08/29 16:34:24 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*sb;

	if (n == 0)
		return ;
	sb = s;
	i = 0;
	while (i < n)
	{
		sb[i] = 0;
		i++;
	}
}
