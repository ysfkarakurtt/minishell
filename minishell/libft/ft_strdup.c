/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:38:37 by ykarakur          #+#    #+#             */
/*   Updated: 2024/08/29 16:38:40 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*new_arr;
	size_t	arr_len;
	size_t	i;

	arr_len = ft_strlen(s1);
	new_arr = (char *) malloc((arr_len + 1) * sizeof(char));
	if (new_arr == 0)
		return (NULL);
	i = 0;
	while (i < arr_len)
	{
		new_arr[i] = s1[i];
		i++;
	}
	new_arr[i] = '\0';
	return (new_arr);
}
