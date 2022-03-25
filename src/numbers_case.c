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

int	five_eleme_suite_2(t_env *env)
{
	int	c;
	int	location;

	c = -1;
	location = 0;
	if (env->b.tab[env->b.top].value > env->a.tab[3].value
		&& env->b.tab[env->b.top].value < env->a.tab[2].value)
		op_inst(env, "ra");
	if (env->b.tab[env->b.top].value > env->a.tab[2].value
		&& env->b.tab[env->b.top].value < env->a.tab[1].value)
	{
		op_inst(env, "ra");
		op_inst(env, "ra");
	}
	if (env->b.tab[env->b.top].value > env->a.tab[1].value
		&& env->b.tab[env->b.top].value < env->a.tab[0].value)
		op_inst(env, "rra");
	op_inst(env, "pa");
	while (++c < 5)
		if (env->a.tab[c].value < env->a.tab[location].value)
			location = c;
	return (location);
}

void	five_elems_suite(t_env *env)
{
	int	c;
	int	location;

	c = -1;
	location = 0;
	if (env->b.tab[env->b.top].value > env->a.tab[2].value
		&& env->b.tab[env->b.top].value < env->a.tab[1].value)
		op_inst(env, "ra");
	if (env->b.tab[env->b.top].value > env->a.tab[1].value
		&& env->b.tab[env->b.top].value < env->a.tab[0].value)
		op_inst(env, "rra");
	op_inst(env, "pa");
	while (++c < 4)
		if (env->a.tab[c].value < env->a.tab[location].value)
			location = c;
	if (location == 0)
		op_inst(env, "rra");
	if (location == 1)
	{
		op_inst(env, "ra");
		op_inst(env, "ra");
	}
	if (location == 2)
		op_inst(env, "ra");
}

void	five_elems(t_env *env)
{
	int	location;

	op_inst(env, "pb");
	op_inst(env, "pb");
	three_elems(env);
	five_elems_suite(env);
	location = five_eleme_suite_2(env);
	if (location == 0)
		op_inst(env, "rra");
	if (location == 1)
	{
		op_inst(env, "rra");
		op_inst(env, "rra");
	}
	if (location == 2)
	{
		op_inst(env, "ra");
		op_inst(env, "ra");
	}
	if (location == 3)
		op_inst(env, "ra");
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
