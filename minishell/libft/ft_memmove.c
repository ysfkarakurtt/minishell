/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:37:32 by ykarakur          #+#    #+#             */
/*   Updated: 2024/08/29 16:37:43 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*dstch;
	unsigned char	*srcch;

	if (dst == src || !len)
		return (dst);
	else if (dst < src)
		return (ft_memcpy(dst, src, len));
	else
	{
		i = len;
		dstch = (unsigned char *) dst;
		srcch = (unsigned char *) src;
		while (i > 0)
		{
			dstch[i - 1] = srcch[i - 1];
			i--;
		}
	}
	return (dst);
}
