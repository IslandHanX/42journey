/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prt_hexa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhan <xhan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:05:02 by xhan              #+#    #+#             */
/*   Updated: 2024/07/02 20:58:18 by xhan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_hex_len(unsigned	int num)
{
	int	len;

	len = 0;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

void	put_hexa(unsigned int nbr, bool upper_case)
{
	char const	*base_upper;
	char const	*base_lower;

	base_upper = "0123456789ABCDEF";
	base_lower = "0123456789abcdef";
	if (nbr >= 16)
		put_hexa((nbr / 16), upper_case);
	if (upper_case)
		write(1, &base_upper[nbr % 16], 1);
	else
		write(1, &base_lower[nbr % 16], 1);
}

int	prt_hexa(unsigned int nbr, bool upper_case)
{
	put_hexa(nbr, upper_case);
	return (ft_hex_len(nbr));
}
