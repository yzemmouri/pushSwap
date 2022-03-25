/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzemmour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 19:38:14 by yzemmour          #+#    #+#             */
/*   Updated: 2022/01/14 19:38:16 by yzemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	free_all(t_env *env)
{
	free(env->a.tab);
	free(env->b.tab);
	free_insts(env->insts);
}

void	insert_numbers(t_env *env, int ac, char **av)
{
	int		i;

	env->a.tab = (t_indexed_value *)malloc((ac - 1 - env->fl)
			* sizeof(t_indexed_value));
	env->a.top = -1;
	env->b.tab = (t_indexed_value *)malloc((ac - 1 - env->fl)
			* sizeof(t_indexed_value));
	env->b.top = -1;
	i = ac - 1 + 1;
	while (--i > env->fl)
	{
		is_valid_args(av[i]);
		env->a.tab[ac - i - 1].value = ft_atoi(av[i]);
		env->a.tab[ac - i - 1].index = ac - i - 1;
		++env->a.top;
		is_doubling_indexed(env->a);
	}
	if (env->sdl.is_visu)
		init_sdl(&env->sdl);
	merge_sort(env->a.tab, 0, ac - 2 - env->fl, 1);
	i = -1;
	while (++i < ac - 1 - env->fl)
		env->a.tab[i].equiv = i;
	merge_sort(env->a.tab, 0, ac - 2 - env->fl, 0);
}

void	numbers_cases(t_env *env, int ac)
{
	if (ac - 1 == 3)
		three_elems(env);
	else if (ac -1 == 5)
		five_elems(env);
	else if (ac - 1 <= 500)
		env->insts = complex_sort(env);
}

void	flags_args(t_env *env, int ac, char **av)
{
	env->fl = 0;
	if (ac >= 2 && (ft_strcmp(av[1], "-v") == 0 || ft_strcmp(av[1], "-c") == 0))
	{
		if (ft_strcmp(av[1], "-v") == 0)
			env->sdl.is_visu = 1;
		if (ft_strcmp(av[1], "-c") == 0)
			env->sdl.vis_col = 1;
		env->fl++;
	}
	if (ac >= 3 && (ft_strcmp(av[2], "-c") == 0 || ft_strcmp(av[2], "-v") == 0))
	{
		if (ft_strcmp(av[2], "-v") == 0)
			env->sdl.is_visu = 1;
		if (ft_strcmp(av[2], "-c") == 0)
			env->sdl.vis_col = 1;
		env->fl++;
	}
}

int	main(int ac, char **av)
{
	t_env	env;

	env.insts = NULL;
	flags_args(&env, ac, av);
	if (ac == 3 && env.sdl.vis_col && env.sdl.is_visu)
		return (0);
	else if (ac == 2 && (env.sdl.vis_col || env.sdl.is_visu))
		return (0);
	else if (ac < 2)
		return (0);
	else
	{
		insert_numbers(&env, ac, av);
		if (is_sorted_indexed_array(env.a.tab, ac - 1 - env.fl))
			return (0);
		else
			numbers_cases(&env, ac - env.fl);
		while (env.b.top > -1)
			op_inst(&env, "pa");
		print_insts(env.insts);
		if (env.sdl.is_visu)
			loop_program(&env.sdl);
		free_all(&env);
	}
	return (0);
}
