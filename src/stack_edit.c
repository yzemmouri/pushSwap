/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_edit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzemmour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 01:32:18 by yzemmour          #+#    #+#             */
/*   Updated: 2022/03/24 01:32:21 by yzemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

t_inst	*put_elem_top_b(t_env *env, int num, t_inst *inst_b)
{
	int	j;

	if (num >= ((env->b.top) / 2))
	{
		j = env->b.top - num;
		while (j > 0)
		{
			inst_b = add_inst(inst_b, "rb");
			manage_indexed_stack(&env->sdl, &env->a, &env->b, "rb");
			j--;
		}
	}
	else
	{
		j = num + 1;
		while (j > 0)
		{
			inst_b = add_inst(inst_b, "rrb");
			manage_indexed_stack(&env->sdl, &env->a, &env->b, "rrb");
			j--;
		}
	}
	return (inst_b);
}

t_inst	*close_rot(t_env *env, t_inst *inst_b, int c, t_len l)
{
	int		j;
	char	*op;

	if (l.rb <= l.rrb)
	{
		j = env->b.top - env->n;
		op = "rb";
	}
	else
	{
		j = env->n + 1;
		op = "rrb";
	}
	env->temp = j;
	while (j > 0)
	{
		inst_b = add_inst(inst_b, op);
		if (c)
			manage_indexed_stack(&env->sdl, &env->a, &env->b, op);
		j--;
	}
	return (inst_b);
}

t_inst	*push_b_op(t_env *env, t_inst *inst_a, t_inst *inst_b, int c)
{
	int		a_inst_len;
	char	*a_inst_type;
	t_len	l;

	a_inst_len = 0;
	l = (t_len){env->b.top - env->n, env->n + 1};
	if (inst_a)
	{
		a_inst_type = inst_a->value;
		while (inst_a)
		{
			++a_inst_len;
			inst_a = inst_a->next;
		}
		if (ft_strcmp(a_inst_type, "ra") == 0)
			l = (t_len){ft_max_i(a_inst_len + 1, l.rb), a_inst_len + 1 + l.rrb};
		else
			l = (t_len){a_inst_len + 1 + l.rb, ft_max_i(a_inst_len + 1, l.rrb)};
	}
	return (close_rot(env, inst_b, c, l));
}

t_inst	*put_elem_top_a(t_env *env, int num, t_inst *inst, int c)
{
	int		j;
	char	*op;

	if (num >= (int)(env->a.top / 2))
	{
		j = env->a.top - num;
		op = "ra";
	}
	else
	{
		j = num + 1;
		op = "rra";
	}
	env->temp = j;
	while (j > 0)
	{
		inst = add_inst(inst, op);
		if (c)
			manage_indexed_stack(&env->sdl, &env->a, &env->b, op);
		j--;
	}
	return (inst);
}

t_inst	*put_elem_position(t_env *env, t_inst *inst_a, t_inst *inst_b, int c)
{
	int	i;

	i = env->b.top - 1;
	while (i >= 0)
	{
		if (env->b.tab[i].equiv < env->m && env->b.tab[i + 1].equiv > env->m)
		{
			env->n = i;
			inst_b = push_b_op(env, inst_a, inst_b, c);
			break ;
		}
		i--;
	}
	return (inst_b);
}
