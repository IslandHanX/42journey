/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prt_unsigned.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhan <xhan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:05:11 by xhan              #+#    #+#             */
/*   Updated: 2024/07/02 20:58:25 by xhan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	unsigned_num_length(unsigned int n)
{
	int	len;

	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_uitoa(unsigned int n)
{
	char	*num;
	int		len;

	len = unsigned_num_length(n);
	num = (char *)malloc(sizeof(char) * (len + 1));
	if (!num)
		return (0);
	num[len] = '\0';
	while (n)
	{
		num[len - 1] = n % 10 + '0';
		n /= 10;
		len--;
	}
	return (num);
}

int	prt_unsigned(unsigned int n)
{
	int		prt_length;
	char	*num;

	prt_length = 0;
	if (n == 0)
		prt_length = write(1, "0", 1);
	else
	{
		num = ft_uitoa(n);
		prt_length = prt_str(num);
		free(num);
	}
	return (prt_length);
}
