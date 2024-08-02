/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhan <xhan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:49:22 by xhan              #+#    #+#             */
/*   Updated: 2024/06/04 21:03:29 by xhan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!*to_find)
		return ((char *)str);
	while (str[j] && j < len)
	{
		i = 0;
		while (str[j + i] == to_find[i] && (j + i) < len)
		{
			if (to_find[i + 1] == '\0')
			{
				return ((char *)str + j);
			}
			i++;
		}
		j++;
	}
	return (NULL);
}
