/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzemmour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 23:28:08 by yzemmour          #+#    #+#             */
/*   Updated: 2022/03/23 23:28:11 by yzemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	init_tools_merge(t_merge *t, t_merge val)
{
	t->i = val.i;
	t->j = val.j;
	t->k = val.k;
	t->n1 = val.n1;
	t->n2 = val.n2;
	t->type = val.type;
}

void	merge_insert(t_indexed_value *stack, t_merge t, t_indexed_value *l,
t_indexed_value *r)
{
	while (t.i < t.n1)
	{
		stack[t.k] = l[t.i];
		t.i++;
		t.k++;
	}
	while (t.j < t.n2)
	{
		stack[t.k] = r[t.j];
		t.j++;
		t.k++;
	}
}

void	merge_by_type(t_merge *t, t_indexed_value *l,
t_indexed_value *r, t_indexed_value *stack)
{
	if (t->type)
	{
		if (l[t->i].value <= r[t->j].value)
			stack[t->k] = l[t->i++];
		else
			stack[t->k] = r[t->j++];
	}
	else
	{
		if (l[t->i].index <= r[t->j].index)
			stack[t->k] = l[t->i++];
		else
			stack[t->k] = r[t->j++];
	}
}

void	merge(t_indexed_value *stack, t_merge_param merge_par, int by_val)
{
	t_merge			t;
	t_indexed_value	*l;
	t_indexed_value	*r;

	l = (t_indexed_value *)malloc((merge_par.m - merge_par.l + 1)
			* sizeof(t_indexed_value));
	r = (t_indexed_value *)malloc((merge_par.r - merge_par.m)
			* sizeof(t_indexed_value));
	init_tools_merge(&t, (t_merge){-1, -1, merge_par.l, merge_par.m
		- merge_par.l + 1, merge_par.r - merge_par.m, by_val});
	while (++t.i < t.n1)
		l[t.i] = stack[merge_par.l + t.i];
	while (++t.j < t.n2)
		r[t.j] = stack[merge_par.m + 1 + t.j];
	t.i = 0;
	t.j = 0;
	while (t.i < t.n1 && t.j < t.n2)
	{
		merge_by_type(&t, l, r, stack);
		t.k++;
	}
	merge_insert(stack, t, l, r);
	free(l);
	free(r);
}

void	merge_sort(t_indexed_value *stack, int l, int r, int by_val)
{
	int				m;
	t_merge_param	merge_par;

	if (l < r)
	{
		m = l + (r - l) / 2;
		merge_sort(stack, l, m, by_val);
		merge_sort(stack, m + 1, r, by_val);
		merge_par = (t_merge_param){r, l, m};
		merge(stack, merge_par, by_val);
	}
}
