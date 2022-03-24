/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_stack.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzemmour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 00:07:37 by yzemmour          #+#    #+#             */
/*   Updated: 2022/03/24 00:07:39 by yzemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	sx_inst(t_stack *s)
{
	if (s->top > 0)
		ft_swap(s->tab + s->top, s->tab + s->top - 1);
}

void	ss_inst(t_stack *s1, t_stack *s2)
{
	sx_inst(s1);
	sx_inst(s2);
}

void	px_inst(t_stack *s1, t_stack *s2)
{
	if (s2->top >= 0)
	{
		s1->top = ++s1->top;
		s1->tab[s1->top] = s2->tab[s2->top];
		s2->top = --s2->top;
	}
}

void	rot_inst(t_stack *s, int to_up)
{
	int	i;
	int	tmp;
	int	limit;

	if (s->top > 0)
	{
		if (to_up)
		{
			i = s->top + 1;
			tmp = s->tab[s->top];
			limit = 0;
			while (--i > limit)
				s->tab[i] = s->tab[i - 1];
		}
		else
		{
			i = -1;
			tmp = s->tab[0];
			limit = s->top;
			while (++i < limit)
				s->tab[i] = s->tab[i + 1];
		}
		s->tab[i] = tmp;
	}
}

void	rot_rot_inst(t_stack *sa, t_stack *sb, int to_up)
{
	rot_inst(sa, to_up);
	rot_inst(sb, to_up);
}
