/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prt_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhan <xhan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:54:43 by xhan              #+#    #+#             */
/*   Updated: 2024/07/02 20:58:21 by xhan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	prt_int(int n)
{
	int		len;
	char	*num;

	len = 0;
	num = ft_itoa(n);
	len = prt_str(num);
	free(num);
	return (len);
}
