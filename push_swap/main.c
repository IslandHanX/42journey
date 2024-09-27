/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhan <xhan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 18:53:55 by xhan              #+#    #+#             */
/*   Updated: 2024/09/18 18:05:06 by xhan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_stack(t_stack_node **a, t_stack_node **b)
{
	if (stack_len(*a) == 2)
		sa(a, false);
	else if (stack_len(*a) == 3)
		tiny_sort(a);
	else
		push_swap(a, b);
}

int	main(int argc, char **argv)
{
	t_stack_node	*a;
	t_stack_node	*b;
	bool			is_split;

	a = NULL;
	b = NULL;
	is_split = false;
	if (argc == 1 || (argc == 2 && !argv[1][0]))
		return (0);
	if (argc == 2)
	{
		argv = ft_split(argv[1], ' ');
		is_split = true;
		stack_init(&a, argv, is_split);
		free_argv(argv);
	}
	else if (argc > 2)
		stack_init(&a, argv + 1, is_split);
	if (!stack_sorted(a))
		sort_stack(&a, &b);
	return (free_stack(&a), 0);
}
/* 如果argc超过2个，就跳过 argv[0]，即程序名 */
