/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhan <xhan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 10:07:07 by xhan              #+#    #+#             */
/*   Updated: 2024/09/18 17:20:52 by xhan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate(t_stack_node **stack)
{
	t_stack_node	*last_node;
	int				len;

	len = stack_len(*stack);
	if (NULL == stack || NULL == *stack || 1 == len)
		return ;
	last_node = find_last_node(*stack);
	last_node->next = *stack;
	*stack = (*stack)->next;
	(*stack)->prev = NULL;
	last_node->next->prev = last_node;
	last_node->next->next = NULL;
}
/*
1. 找到最后一个节点：last_node 指向 节点4。
2. 将最后一个节点的 next 指向头节点：
3. 移动头指针：头指针 *stack 现在指向 节点2。
4. 更新新头节点的 prev 指针：节点2 的 prev 设为 NULL。
5. 更新原头节点（现在在末尾）的指针：
节点1 的 prev 指向 last node。
节点1 的 next 设为 NULL。
*/

void	ra(t_stack_node **a, bool checker)
{
	rotate(a);
	if (!checker)
		write(1, "ra\n", 3);
}

void	rb(t_stack_node **b, bool checker)
{
	rotate(b);
	if (!checker)
		write(1, "rb\n", 3);
}

void	rr(t_stack_node **a, t_stack_node **b, bool checker)
{
	rotate(a);
	rotate(b);
	if (!checker)
		write(1, "rr\n", 3);
}

void	rotate_both(t_stack_node **a,
						t_stack_node **b,
						t_stack_node *cheapest_node)
{
	while (*b != cheapest_node->target_node
		&& *a != cheapest_node)
		rr(a, b, false);
	set_current_position(*a);
	set_current_position(*b);
}
/* 更新当前位置在中线上/中线下。*/
