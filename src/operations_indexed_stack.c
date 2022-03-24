/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_indexed_stack.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzemmour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 23:48:52 by yzemmour          #+#    #+#             */
/*   Updated: 2022/03/23 23:48:54 by yzemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	sx_inst_indexed(t_indexed_stack *s)
{
	t_indexed_value	tmp;

	if (s->top > 0)
	{
		tmp = *(s->tab + s->top);
		*(s->tab + s->top) = *(s->tab + s->top - 1);
		*(s->tab + s->top - 1) = tmp;
	}
}

void	ss_inst_indexed(t_indexed_stack *s1, t_indexed_stack *s2)
{
	sx_inst_indexed(s1);
	sx_inst_indexed(s2);
}

void	px_inst_indexed(t_indexed_stack *s1, t_indexed_stack *s2)
{
	if (s2->top >= 0)
	{
		++s1->top;
		s1->tab[s1->top] = s2->tab[s2->top];
		--s2->top;
	}
}

void	rot_inst_indexed(t_indexed_stack *s, int to_up)
{
	int				i;
	t_indexed_value	tmp;
	int				limit;

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

void	rot_rot_inst_indexed(t_indexed_stack *a, t_indexed_stack *b, int to_up)
{
	rot_inst_indexed(a, to_up);
	rot_inst_indexed(b, to_up);
}
