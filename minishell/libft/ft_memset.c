/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:37:39 by ykarakur          #+#    #+#             */
/*   Updated: 2024/08/29 16:37:41 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*bn;

	bn = (unsigned char *) b;
	i = 0;
	while (i < len)
	{
		bn[i] = (unsigned char) c;
		i++;
	}
	return (b);
}
