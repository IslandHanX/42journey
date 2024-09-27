/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhan <xhan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:36:18 by xhan              #+#    #+#             */
/*   Updated: 2024/09/23 20:51:01 by xhan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_stack(t_stack_node **stack)
{
	t_stack_node	*tmp;
	t_stack_node	*current;

	if (!stack)
		return ;
	current = *stack;
	while (current)
	{
		tmp = current->next;
		free(current);
		current = tmp;
	}
	*stack = NULL;
}
/*堆栈（stack）是以链表形式实现的，每个节点（t_stack_node）都是通过
动态内存分配（例如 malloc）单独分配的。

动态内存分配：由于每个节点都是独立分配的，所以需要逐个释放。
直接调用 free(*stack) 或 free(stack) 只能释放第一个节点或指针本身，无法释放整个链表。

tmp的作用：释放后的访问：在执行 free(current); 后，current 已经不再指向有效的内存。
尝试访问 current->next（即已释放内存的内容）是非法的，可能导致程序异常。*/

void	error_free(t_stack_node **a, char **argv, bool is_split)
{
	if (a)
		free_stack(a);
	if (is_split && argv)
		free_argv(argv);
	write(2, "Error\n", 6);
	exit(1);
}
/* exit(1)：用于终止程序执行，并向操作系统返回状态码 1，表示程序因错误而异常结束。 */

int	error_syntax(char *str_nbr)
{
	if (!(*str_nbr == '+'
			|| *str_nbr == '-'
			|| (*str_nbr >= '0' && *str_nbr <= '9')))
		return (1);
	if ((*str_nbr == '+'
			|| *str_nbr == '-')
		&& !(str_nbr[1] >= '0' && str_nbr[1] <= '9'))
		return (1);
	while (*++str_nbr)
	{
		if (!(*str_nbr >= '0' && *str_nbr <= '9'))
			return (1);
	}
	return (0);
}

int	error_repetition(t_stack_node *a, int nbr)
{
	if (!a)
		return (0);
	while (a)
	{
		if (a->value == nbr)
			return (1);
		a = a->next;
	}
	return (0);
}
