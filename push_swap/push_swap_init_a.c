/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_init_a.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhan <xhan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:02:48 by xhan              #+#    #+#             */
/*   Updated: 2024/09/18 16:59:33 by xhan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	set_current_position(t_stack_node *stack)
{
	int	i;
	int	centerline;

	i = 0;
	if (!stack)
		return ;
	centerline = stack_len(stack) / 2;
	while (stack)
	{
		stack->current_position = i;
		if (i <= centerline)
			stack->above_median = true;
		else
			stack->above_median = false;
		stack = stack->next;
		++i;
	}
}
/*
更新某个 node 的 bool 值 是否高于中位线。
*/

static void	set_target_node(t_stack_node *a,
							t_stack_node *b)
{
	t_stack_node	*current_b;
	t_stack_node	*target_node;
	long			best_match_index;

	while (a)
	{
		best_match_index = LONG_MIN;
		current_b = b;
		while (current_b)
		{
			if (current_b->value < a->value
				&& current_b->value > best_match_index)
			{
				best_match_index = current_b->value;
				target_node = current_b;
			}
			current_b = current_b->next;
		}
		if (best_match_index == LONG_MIN)
			a->target_node = find_biggest(b);
		else
			a->target_node = target_node;
		a = a->next;
	}
}
/*
帮a中的每一个 node 找到b里的 closest smaller 也就是target node。
如果找不到 closest smaller 那么target node 就是b里最大的值。
*/

void	set_price(t_stack_node *a, t_stack_node *b)
{
	int	len_a;
	int	len_b;

	len_a = stack_len(a);
	len_b = stack_len(b);
	while (a)
	{
		a->push_price = a->current_position;
		if (!(a->above_median))
			a->push_price = len_a - (a->current_position);
		if (a->target_node->above_median)
			a->push_price += a->target_node->current_position;
		else
			a->push_price += len_b - (a->target_node->current_position);
		a = a->next;
	}
}
/*
算出每个a里的node 的push price 并且存放在node 信息里。
*/

void	set_cheapest(t_stack_node *stack)
{
	long			best_match_value;
	t_stack_node	*best_match_node;

	if (!stack)
		return ;
	best_match_value = LONG_MAX;
	while (stack)
	{
		if (stack->push_price < best_match_value)
		{
			best_match_value = stack->push_price;
			best_match_node = stack;
		}
		stack = stack->next;
	}
	if (best_match_node)
		best_match_node->cheapest = true;
}
/*push代价最小的node 被用cheapest 标记。*/

void	init_nodes(t_stack_node *a, t_stack_node *b)
{
	set_current_position(a);
	set_current_position(b);
	set_target_node(a, b);
	set_price(a, b);
	set_cheapest(a);
}
/*
刷新所有信息，为push作准备。
*/
