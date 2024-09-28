/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhan <xhan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:25:55 by xhan              #+#    #+#             */
/*   Updated: 2024/06/04 20:32:08 by xhan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memchr(const void *str, int c, size_t size)
{
	while (size--)
	{
		if (*(unsigned char *)str == (unsigned char)c)
			return ((unsigned char *)str);
		str++;
	}
	return (NULL);
}
// converting to unsigned char to make sure 
// that it process by byte