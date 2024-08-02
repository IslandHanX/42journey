/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhan <xhan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:52:02 by xhan              #+#    #+#             */
/*   Updated: 2024/06/03 14:02:57 by xhan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dst;

	dst = dest;
	if (!dest && !src)
		return (dest);
	while (n-- > 0)
	{
		*dst++ = *(unsigned char *)src++;
	}
	return (dest);
}
