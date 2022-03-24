/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzemmour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 18:14:18 by yzemmour          #+#    #+#             */
/*   Updated: 2022/01/14 18:14:20 by yzemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	is_valid_args(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-')
		i++;
	while (arg[i] != '\0')
	{
		if (ft_isdigit(arg[i]) == 0)
			error("Error");
		is_int_range(arg, "-2147483648", "2147483647");
		i++;
	}
}

void	is_doubling(t_stack s)
{
	int	i;

	i = 0;
	while (i < s.top)
	{
		if (s.tab[i] == s.tab[s.top])
			error("Error");
		i++;
	}
}

void	is_doubling_indexed(t_indexed_stack s)
{
	int	i;

	i = 0;
	while (i < s.top)
	{
		if (s.tab[i].value == s.tab[s.top].value)
			error("Error");
		i++;
	}
}

int	is_valid_instuction(char	*inst)
{
	if (ft_strcmp(inst, "sa") && ft_strcmp(inst, "sb")
		&& ft_strcmp(inst, "ss") && ft_strcmp(inst, "pa")
		&& ft_strcmp(inst, "pb") && ft_strcmp(inst, "ra")
		&& ft_strcmp(inst, "rb") && ft_strcmp(inst, "rr")
		&& ft_strcmp(inst, "rra") && ft_strcmp(inst, "rrb")
		&& ft_strcmp(inst, "rrr"))
		return (0);
	return (1);
}
