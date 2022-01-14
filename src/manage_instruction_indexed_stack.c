/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_instruction_indexed_stack.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzemmour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 18:18:06 by yzemmour          #+#    #+#             */
/*   Updated: 2022/01/14 18:18:09 by yzemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_swap_indexed(t_indexed_value *elem1, t_indexed_value *elem2)
{
	t_indexed_value	tmp;

	tmp = *elem1;
	*elem1 = *elem2;
	*elem2 = tmp;
}

void	sx_instr(t_indexed_stack *s)
{
	if (s->top > 0)
		ft_swap_indexed(s->tab + s->top, s->tab + s->top - 1);
}

void	ss_instr(t_indexed_stack *s1, t_indexed_stack *s2)
{
	sx_instr(s1);
	sx_instr(s2);
}

void	px_instr(t_indexed_stack *s1, t_indexed_stack *s2)
{
	if (s2->top >= 0)
	{
		++s1->top;
		s1->tab[s1->top] = s2->tab[s2->top];
		--s2->top;
	}
}

void	rot_instr(t_indexed_stack *s, int to_up)
{
	int				i;
	t_indexed_value	tmp;
	int				limit;

	if (s->top > 0)
	{
		if (to_up)
		{
			i = s->top;
			tmp = s->tab[s->top];
			limit = 0;
		}
		else
		{
			i = 0;
			tmp = s->tab[0];
			limit = s->top;
		}
		if (to_up)
		{
			while (i > limit)
			{
				s->tab[i] = s->tab[i - 1];
				--i;
			}
		}
		else
		{
			while (i < limit)
			{
				s->tab[i] = s->tab[i + 1];
				++i;
			}
		}
		s->tab[i] = tmp;
	}
}

void	rot_rot_instr(t_indexed_stack *a, t_indexed_stack *b, int to_up)
{
	rot_instr(a->tab, to_up);
	rot_instr(b->tab, to_up);
}

void	manage_instruction_indexed_stack(t_sdl *data,
	t_indexed_stack *sa, t_indexed_stack *sb,
	char *instr)
{
	if (ft_strcmp(instr, "sa") == 0)
		sx_instr(sa);
	else if (ft_strcmp(instr, "sb") == 0)
		sx_instr(sb);
	else if (ft_strcmp(instr, "ss") == 0)
		ss_instr(sa, sb);
	else if (ft_strcmp(instr, "pa") == 0)
		px_instr(sa, sb);
	else if (ft_strcmp(instr, "pb") == 0)
		px_instr(sb, sa);
	else if (ft_strcmp(instr, "ra") == 0)
		rot_instr(sa, 1);
	else if (ft_strcmp(instr, "rb") == 0)
		rot_instr(sb, 1);
	else if (ft_strcmp(instr, "rr") == 0)
		rot_rot_instr(sa, sb, 1);
	else if (ft_strcmp(instr, "rra") == 0)
		rot_instr(sa, 0);
	else if (ft_strcmp(instr, "rrb") == 0)
		rot_instr(sb, 0);
	else if (ft_strcmp(instr, "rrr") == 0)
		rot_rot_instr(sa, sb, 0);
	if (is_option_activated(data->options, V_OPTION))
		draw(data, *sa, *sb);
}
