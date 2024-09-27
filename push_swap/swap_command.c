/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhan <xhan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 09:53:41 by xhan              #+#    #+#             */
/*   Updated: 2024/09/18 17:19:07 by xhan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap(t_stack_node **head)
{
	int	len;

	len = stack_len(*head);
	if (*head == NULL || head == NULL || len == 1)
		return ;
	*head = (*head)->next;
	(*head)->prev->prev = *head;
	(*head)->prev->next = (*head)->next;
	if ((*head)->next)
		(*head)->next->prev = (*head)->prev;
	(*head)->next = (*head)->prev;
	(*head)->prev = NULL;
}
/*
将头指针移动到第二个节点 - 更新原头节点的 prev 指针 - 更新原头节点的 next 指针 - 
更新新头节点的下一个节点的 prev 指针（如果存在） - 更新新头节点的 next 指针 - 
更新新头节点的 prev 指针

Node1 是原头节点，head 指向它。
Node1->next = Node2
Node2->prev = Node1
交换后，链表如下：
Node2 成为新的头节点，head 指向它。
Node2->prev = NULL
Node2->next = Node1
Node1->prev = Node2
Node1->next = Node3
Node3->prev 需要更新为 Node1（如果存在）。
*/

void	sa(t_stack_node	**a, bool checker)
{
	swap(a);
	if (!checker)
		write(1, "sa\n", 3);
}

void	sb(t_stack_node **b, bool checker)
{
	swap(b);
	if (!checker)
		write(1, "sb\n", 3);
}

void	ss(t_stack_node **a, t_stack_node **b, bool checker)
{
	swap(a);
	swap(b);
	if (!checker)
		write(1, "ss\n", 3);
}
