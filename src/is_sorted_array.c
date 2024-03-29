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
