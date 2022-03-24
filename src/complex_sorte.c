/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_sorte.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzemmour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 01:52:45 by yzemmour          #+#    #+#             */
/*   Updated: 2022/03/24 01:52:48 by yzemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	find_max(t_indexed_stack s)
{
	int	i;
	int	max;
	int	index;

	max = s.tab[s.top].equiv;
	index = s.top;
	i = s.top - 1;
	while (i >= 0)
	{
		if (s.tab[i].equiv > max)
		{
			max = s.tab[i].equiv;
			index = i;
		}
		i--;
	}
	return (index);
}

t_inst	*fusion_suite(t_inst *insts, t_inst *tmp1, t_inst *tmp2)
{
	while (tmp2)
	{
		insts = add_inst(insts, tmp2->value);
		tmp2 = tmp2->next;
	}
	while (tmp1)
	{
		insts = add_inst(insts, tmp1->value);
		tmp1 = tmp1->next;
	}
	return (insts);
}

t_inst	*fusion(t_inst *insts, t_inst *insts_a, t_inst *insts_b)
{
	t_inst	*tmp1;
	t_inst	*tmp2;

	tmp1 = insts_a;
	tmp2 = insts_b;
	while (tmp1 && tmp2)
	{
		if (ft_strcmp(tmp1->value, "ra") == 0
			&& ft_strcmp(tmp2->value, "rb") == 0)
			insts = add_inst(insts, "rr");
		else if (ft_strcmp(tmp1->value, "rra") == 0
			&& ft_strcmp(tmp2->value, "rrb") == 0)
			insts = add_inst(insts, "rrr");
		else
		{
			insts = add_inst(insts, tmp2->value);
			insts = add_inst(insts, tmp1->value);
		}
		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}
	return (fusion_suite(insts, tmp1, tmp2));
}

t_inst	*complex_sort(t_env *env)
{
	int		index;
	t_inst	*insts_a;
	t_inst	*insts_b;

	insts_a = NULL;
	insts_b = NULL;
	while (env->a.top >= 0)
	{
		index = best_elem(env);
		insts_a = put_elem_top_a(env, index, insts_a, 1);
		insts_b = positon_in_a(env, insts_a, insts_b);
		env->insts = fusion(env->insts, insts_a, insts_b);
		insts_a = free_insts(insts_a);
		insts_b = free_insts(insts_b);
		env->insts = add_inst(env->insts, "pb");
		manage_indexed_stack(&env->sdl, &env->a, &env->b, "pb");
	}
	env->insts = put_elem_top_b(env, find_max(env->b), env->insts);
	return (env->insts);
}
