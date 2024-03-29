/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_int_range.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzemmour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 13:11:40 by yzemmour          #+#    #+#             */
/*   Updated: 2022/01/14 13:11:44 by yzemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	is_int_range(char *number, char min_int[11], char max_int[10])
{
	int		length;
	char	is_negative;
	int		i;
	char	*p;

	if (number[0] == '-')
		is_negative = 1;
	else
		is_negative = 0;
	length = ft_strlen(number);
	if (is_negative && length > 11)
		error("Error");
	else if (!is_negative && length > 10)
		error("Error");
	if ((is_negative && length == 11) || (!is_negative && length == 10))
	{
		i = -1;
		if (is_negative)
			p = min_int;
		else
			p = max_int;
		while (++i < length)
			if (number[i] > p[i])
				error("Error");
	}
}
