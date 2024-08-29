/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:39:22 by ykarakur          #+#    #+#             */
/*   Updated: 2024/08/29 16:39:25 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char				*n_str;
	unsigned int		i;

	i = 0;
	n_str = ft_strdup(s);
	if (!n_str)
		return (0);
	while (s[i])
	{
		n_str[i] = f(i, s[i]);
		i++;
	}
	return (n_str);
}
