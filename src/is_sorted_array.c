/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sorted_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzemmour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 13:15:10 by yzemmour          #+#    #+#             */
/*   Updated: 2022/01/14 13:15:12 by yzemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	is_sorted_array(int *a, int n)
{
	if (n == 1 || n == 0)
		return (1);
	return (a[n - 1] <= a[n - 2] && is_sorted_array(a, n - 1));
}

int	is_sorted_indexed_array(t_indexed_value *a, int n)
{
	if (n == 1 || n == 0)
		return (1);
	return (a[n - 1].value <= a[n - 2].value
		&& is_sorted_indexed_array(a, n - 1));
}

void	init_tools_merge(t_merge_tools *t, t_merge_tools val)
{
	t->i = val.i;
	t->j = val.j;
	t->k = val.k;
	t->n1 = val.n1;
	t->n2 = val.n2;
}

void	merge_insert(t_indexed_value *stack, t_merge_tools t, t_indexed_value *l,
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

void	merge(t_indexed_value *stack, int left, int m, int right, int by_val)
{
	t_merge_tools	t;
	t_indexed_value	l[m - left + 1];
	t_indexed_value	r[right - m];

	init_tools_merge(&t, (t_merge_tools){-1, -1, left, m - left + 1, right - m});
	while (++t.i < t.n1)
		l[t.i] = stack[left + t.i];
	while (++t.j < t.n2)
		r[t.j] = stack[m + 1 + t.j];
	t.i = 0;
	t.j = 0;
	while (t.i < t.n1 && t.j < t.n2)
	{
		if(by_val)
		{
			stack[t.k] = l[t.i].value <= r[t.j].value ? l[t.i] : r[t.j];
			l[t.i].value <= r[t.j].value ? t.i++ : t.j++;
		}
		else
		{
			stack[t.k] = l[t.i].index <= r[t.j].index ? l[t.i] : r[t.j];
			l[t.i].index <= r[t.j].index ? t.i++ : t.j++;
		}
		t.k++;
	}
	merge_insert(stack, t, l, r);
}

void	mergeSort(t_indexed_value *stack, int l, int r, int by_val)
{
	int m;

	if (l < r)
	{
		m = l + (r - l) / 2;
		mergeSort(stack, l, m, by_val);
		mergeSort(stack, m + 1, r, by_val);
		merge(stack, l, m, r, by_val);
	}
}
