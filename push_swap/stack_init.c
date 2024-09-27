/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhan <xhan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:42:38 by xhan              #+#    #+#             */
/*   Updated: 2024/09/23 20:48:31 by xhan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	stack_init(t_stack_node **a, char **argv, bool is_split)
{
	long long	nbr;
	int			i;

	i = 0;
	while (argv[i])
	{
		if (error_syntax(argv[i]))
			error_free(a, argv, is_split);
		nbr = ft_atol(argv[i]);
		if (nbr > INT_MAX || nbr < INT_MIN)
			error_free(a, argv, is_split);
		if (error_repetition(*a, (int)nbr))
			error_free(a, argv, is_split);
		append_node(a, (int)nbr);
		i++;
	}
}
/*
确保在后续将 nbr 转换为 int 时，不会发生数据丢失或溢出。

后续的函数如 error_repetition 和 append_node 是基于
int 类型来设计的，需要接受 int 类型的参数
*/