/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzemmour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 00:43:46 by yzemmour          #+#    #+#             */
/*   Updated: 2022/03/24 00:43:48 by yzemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	five_eleme_suite_2(t_env *env)
{
	if (env->a.tab[4].value > env->a.tab[3].value
		&& env->a.tab[4].value < env->a.tab[2].value)
		op_inst(env, "sa");
	if (env->a.tab[4].value > env->a.tab[2].value
		&& env->a.tab[4].value < env->a.tab[1].value)
	{
		op_inst(env, "sa");
		op_inst(env, "ra");
		op_inst(env, "sa");
		op_inst(env, "rra");
	}
	if (env->a.tab[4].value > env->a.tab[1].value
		&& env->a.tab[4].value < env->a.tab[0].value)
	{
		op_inst(env, "rra");
		op_inst(env, "sa");
		op_inst(env, "ra");
		op_inst(env, "ra");
	}
}

void	five_elems_suite(t_env *env)
{
	int	new_max_min;

	op_inst(env, "pa");
	new_max_min = five_max_min(env->a, env->a.tab[3].value);
	if (new_max_min)
	{
		if (new_max_min == 1)
			op_inst(env, "ra");
	}
	else
	{
		if (env->a.tab[3].value > env->a.tab[2].value
			&& env->a.tab[3].value < env->a.tab[1].value)
			op_inst(env, "sa");
		if (env->a.tab[3].value > env->a.tab[1].value
			&& env->a.tab[3].value < env->a.tab[0].value)
		{
			op_inst(env, "rra");
			op_inst(env, "sa");
			op_inst(env, "ra");
			op_inst(env, "ra");
		}
	}
}

void	five_elems(t_env *env)
{
	int	new_max_min_2;

	op_inst(env, "pb");
	op_inst(env, "pb");
	three_elems(env);
	five_elems_suite(env);
	op_inst(env, "pa");
	new_max_min_2 = five_max_min(env->a, env->a.tab[4].value);
	if (new_max_min_2 != 0)
	{
		if (new_max_min_2 == 1)
			op_inst(env, "ra");
	}
	else
		five_eleme_suite_2(env);
}

void	tree_elems_suite(t_env *env)
{
	if (env->a.tab[0].value < env->a.tab[1].value
		&& env->a.tab[1].value > env->a.tab[2].value
		&& env->a.tab[0].value > env->a.tab[2].value)
	{
		op_inst(env, "sa");
		op_inst(env, "ra");
	}
	if (env->a.tab[0].value < env->a.tab[1].value
		&& env->a.tab[1].value < env->a.tab[2].value
		&& env->a.tab[0].value < env->a.tab[2].value)
	{
		op_inst(env, "sa");
		op_inst(env, "rra");
	}
}

void	three_elems(t_env *env)
{
	if (env->a.tab[0].value > env->a.tab[1].value
		&& env->a.tab[1].value < env->a.tab[2].value
		&& env->a.tab[0].value > env->a.tab[2].value)
		op_inst(env, "sa");
	if (env->a.tab[0].value > env->a.tab[1].value
		&& env->a.tab[1].value < env->a.tab[2].value
		&& env->a.tab[0].value < env->a.tab[2].value)
		op_inst(env, "ra");
	if (env->a.tab[0].value < env->a.tab[1].value
		&& env->a.tab[1].value > env->a.tab[2].value
		&& env->a.tab[0].value < env->a.tab[2].value)
		op_inst(env, "rra");
	tree_elems_suite(env);
}
