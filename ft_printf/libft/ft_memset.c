/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhan <xhan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:47:23 by xhan              #+#    #+#             */
/*   Updated: 2024/06/03 13:40:07 by xhan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memset(void *pointer, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = pointer;
	while (len-- > 0)
	{
		*ptr++ = (unsigned char)c;
	}
	return (pointer);
}

// Using void * allows the function to be applicable to any type of memory 
// area without restricting it to a specific type.
// And use int value is to mimic the standard memset, although only 
// the value within the range of unsigned char is used.
// use unsigned char allow byte-by-byte operations and avoiding issues with 
// sign extension.
