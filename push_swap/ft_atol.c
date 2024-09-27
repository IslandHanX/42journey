/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhan <xhan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 21:03:56 by xhan              #+#    #+#             */
/*   Updated: 2024/09/23 20:38:54 by xhan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	parse_sign(const char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

long long	ft_atol(const char *str)
{
	int			i;
	long long	result;
	int			sign;

	i = 0;
	result = 0;
	while ((str[i] && str[i] == ' ') || ((str[i] <= 13 && str[i] >= 9)))
		i++;
	sign = parse_sign(str, &i);
	while (str[i] && str[i] <= '9' && str[i] >= '0')
	{
		if (result > (LLONG_MAX - (str[i] - '0')) / 10)
		{
			if (sign == 1)
				return (LLONG_MAX);
			else
				return (LLONG_MIN);
		}
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * sign);
}
