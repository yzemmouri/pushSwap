/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_edit_too.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzemmour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 01:45:35 by yzemmour          #+#    #+#             */
/*   Updated: 2022/03/24 01:45:36 by yzemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	list_length(t_inst *list)
{
	t_inst	*cur;
	int		size;

	cur = list;
	size = 0;
	while (cur != NULL)
	{
		++size;
		cur = cur->next;
	}
	return (size);
}

int	is_new_min_max(t_indexed_stack s, int num)
{
	int		i;
	int		max;
	int		index;
	t_len	l;

	l.rb = 1;
	l.rrb = 1;
	max = -1;
	index = -1;
	i = s.top + 1;
	while (--i >= 0)
	{
		if (s.tab[i].equiv > num)
			l.rrb = 0;
		if (s.tab[i].equiv < num)
			l.rb = 0;
		if (s.tab[i].equiv > max)
		{
			max = s.tab[i].equiv;
			index = i;
		}
	}
	if (l.rb || l.rrb)
		return (index);
	return (-1);
}

t_var_best_elem	best_elem_suite(t_env *env, t_var_best_elem	v,
t_inst *insts_a, t_inst *insts_b)
{
	if (env->b.top >= 1)
	{
		v.new_max_min = is_new_min_max(env->b, env->a.tab[v.i].equiv);
		if (v.new_max_min != -1)
		{
			env->n = v.new_max_min;
			insts_b = push_b_op(env, insts_a, insts_b, 0);
			v.len += list_length(insts_b);
		}
		else
		{
			env->m = env->a.tab[v.i].equiv;
			insts_b = put_elem_position(env, insts_a, insts_b, 0);
			v.len += list_length(insts_b);
		}
	}
	return (v);
}

int	best_elem(t_env *env)
{
	t_inst			*insts_a;
	t_inst			*insts_b;
	t_var_best_elem	v;

	insts_a = NULL;
	insts_b = NULL;
	v.i = env->a.top;
	v.min_num_op = 100000000;
	v.best_index = 0;
	while (v.i >= 0)
	{
		insts_a = put_elem_top_a(env, v.i, insts_a, 0);
		v.len = list_length(insts_a);
		v = best_elem_suite(env, v, insts_a, insts_b);
		if (v.len < v.min_num_op)
		{
			v.best_index = v.i;
			v.min_num_op = v.len;
		}
		v.len = 0;
		insts_a = free_insts(insts_a);
		insts_b = free_insts(insts_b);
		v.i--;
	}
	return (v.best_index);
}

t_inst	*positon_in_a(t_env *env, t_inst *insts_a, t_inst *insts_b)
{
	int		new_max_min;

	if (env->b.top >= 1)
	{
		new_max_min = is_new_min_max(env->b, env->a.tab[env->a.top].equiv);
		if (new_max_min != -1)
		{
			env->n = new_max_min;
			insts_b = push_b_op(env, insts_a, insts_b, 1);
		}
		else
		{
			env->m = env->a.tab[env->a.top].equiv;
			insts_b = put_elem_position(env, insts_a, insts_b, 1);
		}
	}
	return (insts_b);
}
