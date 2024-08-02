/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhan <xhan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:09:05 by xhan              #+#    #+#             */
/*   Updated: 2024/06/04 12:43:39 by xhan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcpy(char *dest, char const *src, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (src[i])
	{
		i++;
	}
	if (!n)
		return (i);
	j = 0;
	while (j < (n - 1) && src[j])
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = '\0';
	return (i);
}
