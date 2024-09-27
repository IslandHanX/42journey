/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhan <xhan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:55:38 by xhan              #+#    #+#             */
/*   Updated: 2024/09/26 11:38:28 by xhan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_stack_node
{
	int					value;
	int					current_position;
	int					push_price;
	bool				above_median;
	bool				cheapest;
	struct s_stack_node	*target_node;
	struct s_stack_node	*next;
	struct s_stack_node	*prev;
}				t_stack_node;

char			**ft_split(char const *s, char c);

void			free_argv(char **argv);
void			error_free(t_stack_node **a, char **argv, bool is_split);
void			free_stack(t_stack_node **stack);
int				error_repetition(t_stack_node *a, int nbr);
int				error_syntax(char *str_nbr);

long long		ft_atol(const char *str);
void			stack_init(t_stack_node **a, char **argv, bool is_split);
void			init_nodes(t_stack_node *a, t_stack_node *b);
void			init_nodes_b(t_stack_node *a, t_stack_node *b);
void			set_current_position(t_stack_node *stack);
void			set_price(t_stack_node *a, t_stack_node *b);
void			set_cheapest(t_stack_node *stack);

void			append_node(t_stack_node **stack, int nbr);
t_stack_node	*find_biggest(t_stack_node *stack);
t_stack_node	*find_smallest(t_stack_node *stack);
t_stack_node	*find_last_node(t_stack_node *head);
t_stack_node	*return_cheapest(t_stack_node *stack);
bool			stack_sorted(t_stack_node *stack);
int				stack_len(t_stack_node *stack);
void			prep_push(t_stack_node **s, t_stack_node *n, char c);

/* Algo part */
void			rotate_both(t_stack_node **a, t_stack_node **b,
					t_stack_node *cheapest_node);
void			reverse_rotate_both(t_stack_node **a, t_stack_node **b,
					t_stack_node *cheapest_node);
void			tiny_sort(t_stack_node **a);
void			push_swap(t_stack_node **a, t_stack_node **b);

/* Commands*/
void			sa(t_stack_node **a, bool checker);
void			sb(t_stack_node **b, bool checker);
void			ss(t_stack_node **a, t_stack_node **b, bool checker);
void			ra(t_stack_node **a, bool checker);
void			rb(t_stack_node **b, bool checker);
void			rr(t_stack_node **a, t_stack_node **b, bool checker);
void			rra(t_stack_node **a, bool checker);
void			rrb(t_stack_node **b, bool checker);
void			rrr(t_stack_node **a, t_stack_node **b, bool checker);
void			pa(t_stack_node **a, t_stack_node **b, bool checker);
void			pb(t_stack_node **b, t_stack_node **a, bool checker);

#endif